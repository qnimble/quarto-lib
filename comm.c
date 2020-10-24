#include "imxrt.h"
#include "comm.h"

void setWriteAddress(uint16_t address) {
	GPIO7_DR_TOGGLE = (0x000B0000 + address);
}


void writeData(uint16_t data) {
	GPIO7_DR_TOGGLE = (0x000D0000 + data);
}


uint16_t readData(uint16_t address) {
	volatile uint32_t j=34;
	while(1) {

		GPIO7_DR_TOGGLE = (0x000F0000 + address);
		j = j+j*234+(j*(j+65));
		//printf("Read Data");

		uint i = 0;
		while(readReady() == 0) { //Wait until data ready
			//printf("Waiting for data to be read (attempt %d)...\r\n",i);
			i++;
			if (i > 10){
				printf("Read failed, re-trying\r\n");
				goto final;
			}
		}
		uint16_t read = GPIO6_DR >> 16;
		GPIO6_DR_TOGGLE = 0x00000020; // Tooggle bootmode 1

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
	if ((GPIO7_DR & 0x80000000) == 0x80000000 ){
		return 1;
	} else
		return 0;
}

void QuartoInit(void){
	GPIO6_GDIR |= 0x20; //Set BM1 as output
}
