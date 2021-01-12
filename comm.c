#include "imxrt.h"
#include "comm.h"

#define DAC_WRITE_CMD 0x24


void zeroDACs(void) {
	setWriteAddress(0x24);
	writeData(0x7FFF);
	setWriteAddress(0x25);
	writeData(0x7FFF);
	setWriteAddress(0x26);
	writeData(0x7FFF);
	setWriteAddress(0x27);
	writeData(0x7FFF);
}


void setWriteAddress(uint16_t address) {
	GPIO7_DR_TOGGLE = (0x000B0000 + address);
}


void writeData(uint16_t data) {
	GPIO7_DR_TOGGLE = (0x000D0000 + data);
}


uint16_t writeAndRead(uint16_t address,uint16_t data){
	setWriteAddress(address);
	writeData(data);
	uint16_t result = readData(address);
	if (result != data) {
		printf("Error: got 0x%04x not 0x%04x at addr=0x%04x\r\n",result,data,address);
		return result;
	}
	return result;
}

void writeDAC1(uint16_t data) {
	//GPIO7_DR_TOGGLE = (0x00010000 + data);
	setWriteAddress(DAC_WRITE_CMD);
	writeData(data);
}

void writeDAC2(uint16_t data) {
	//GPIO7_DR_TOGGLE = (0x00030000 + data);
	setWriteAddress(DAC_WRITE_CMD+1);
	writeData(data);
}

void writeDAC3(uint16_t data) {
	//GPIO7_DR_TOGGLE = (0x00050000 + data);
	setWriteAddress(DAC_WRITE_CMD+2);
	writeData(data);
}

void writeDAC4(uint16_t data) {
	//GPIO7_DR_TOGGLE = (0x00070000 + data);
	setWriteAddress(DAC_WRITE_CMD+3);
	writeData(data);
}



uint16_t readData(uint16_t address) {
	volatile uint32_t j=34;
	while(1) {

		GPIO7_DR_TOGGLE = (0x000F0000 + address);
		//j = j+j*234+(j*(j+65));
		//printf("Read Data");

		uint i = 0;
		while(readReady() == 0) { //Wait until data ready
			//printf("Waiting for data to be read (attempt %d)...\r\n",i);
			i++;
			if (i > 10){
				printf("Read failed on address=0x%04x, re-trying\r\n",address);
				goto final;
			}
		}
		uint16_t read = GPIO6_DR >> 16;
		GPIO6_DR_TOGGLE = 0x00000020; // Toggle Read Data ACK

		i=0;
		while(readReady() == 1) { //Wait until data read has been acknowledged
			//printf("Waiting for data read to be ACKd (attempt %d without retoggle)...\r\n",i);
			//GPIO6_DR_TOGGLE = 0x00000020; // Tooggle bootmode 1
			i++;
			if (i%10==0){
				printf("Failed to get ack of read, toggling again\r\n");
				GPIO6_DR_TOGGLE = 0x00000020; // Tooggle bootmode 1
			}
			if (i > 100){
				printf("Giving on read, moving on\r\n");
				return 0;
			}

		}


		//printf(" of @0x%04x\r\n",read);
		return read;

		final:
			continue;
	}
}

uint8_t readReady(void){
	if ((GPIO8_DR & 0x10) == 0x10 ){
		return 1;
	} else
		return 0;
}

void QuartoInit(void){
	GPIO6_GDIR |= 0x30; //Set BM1 as output
	GPIO6_DR_TOGGLE = 0x00000020; // Toggle Read Data ACK
	GPIO6_DR_TOGGLE = 0x00000020; // Toggle Read Data ACK
	GPIO6_DR_TOGGLE = 0x00000020; // Toggle Read Data ACK
	GPIO6_DR_TOGGLE = 0x00000020; // Toggle Read Data ACK
	GPIO6_DR_TOGGLE = 0x00000010; // Tooggle ADC Data ACK
	GPIO6_DR_TOGGLE = 0x00000010; // Tooggle ADC Data ACK
	GPIO6_DR_TOGGLE = 0x00000010; // Tooggle ADC Data ACK
	GPIO6_DR_TOGGLE = 0x00000010; // Tooggle ADC Data ACK
	GPIO6_DR_TOGGLE = 0x00000010; // Tooggle ADC Data ACK
}


int16_t readADC(void) {
	int16_t read = GPIO6_DR >> 16;
	GPIO6_DR_TOGGLE = 0x00000010; // Tooggle bootmode 0
	return read;
}
