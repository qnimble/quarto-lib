/****************************************************************************
 ** comm.c ******************************************************************
 ****************************************************************************
 *
 * Copyright (C) 2021, qNimble (https://qnimble.com)
 * Author: ben-qnimble
 *
 * Distributed under the GPL version 2.0.
 * See LICENSE for license details.
 */


#include "imxrt.h"
#include "comm.h"
#include "pins_arduino.h"

static int _status = 0;

void setWriteAddress(uint16_t address) {
	asm volatile("nop\n");
	GPIO7_DR_TOGGLE = (0x000B0000 + address);
}

void writeData(uint16_t data) {
	asm volatile("nop\n");
	GPIO7_DR_TOGGLE = (0x000D0000 + data);
}

uint16_t writeAndRead(uint16_t address,uint16_t data){
	setWriteAddress(address);
	writeData(data);
	uint16_t loops = 0;
	uint16_t result;
	do {
		result = readData(address);
		loops++;
		if (loops >= 10) {
			_status++;
			return 0xFFFE;
		}
	} while ( result != data);
	
	return result;
}


uint16_t readEEPROM(uint32_t address) {
	uint8_t upper_byte = address>>24;
	setWriteAddress(0x3000 + upper_byte);

	uint16_t middle_part = ((address>>12) & 0x0FFF);
	setWriteAddress(0x2000 + middle_part);

	uint16_t lowest = ((address) & 0x0FFF);
	setWriteAddress(0x1000 + lowest);

	return readData(0x1000);
}


uint16_t readData(uint16_t address) {	
	//GPIO6_DR_SET = 0x02;
	uint full_loops = 0;
	while(1) {
		GPIO7_DR_TOGGLE = (0x000F0000 + address);
		uint i = 0;
		while(readReady() == 0) { //Wait until data ready
			i++;
			if (i > 300){
				//printf("Read failed on address=0x%04x, re-trying\r\n",address);
				goto final;
			}
		}
		uint16_t read = GPIO6_DR >> 16;

		if ( readReady() == 0 ) {
			//Read no longer valid, (ADC data came in), retry
			goto final;
		}

		READDATA_ACK_BANK_TOGGLE = READDATA_ACK_PIN; // Toggle Read Data ACK

		i=0;
		while(readReady() == 1) { //Wait until data read has been acknowledged
			//printf("Waiting for data read to be ACKd (attempt %d without retoggle)...\r\n",i);
			i++;
			if (i%10==0){
				//printf("Failed to get ack of read, toggling again\r\n");				
				READDATA_ACK_BANK_TOGGLE = READDATA_ACK_PIN; // Tooggle bootmode 1
			}
			if (i > 100){
				//printf("Giving up on read, moving on\r\n");
				//Serial.println("Giving up on read, moving on");
				_status++;
				//GPIO6_DR_CLEAR = 0x02;
				return 0;
			}
		}
		//GPIO6_DR_CLEAR = 0x02;

		//printf(" of @0x%04x\r\n",read);
		return read;

		final:
			full_loops++;
			if (full_loops > 10) {
				_status++;
				//GPIO6_DR_CLEAR = 0x02;
				return 0;
			}
			continue;
	}
}


int readStatus(void) {
	return _status;
}


uint8_t readReady(void){
	if ((READDATA_READY_BANK & READDATA_READY_PIN) == READDATA_READY_PIN ){
		return 1;
	} else
		return 0;
}

void ClearDataRequests(void) {
	for(int i=0;i<16;i++) {
		READDATA_ACK_BANK_TOGGLE = READDATA_ACK_PIN; // Toggle Read Data ACK
		ADC_ACK_BANK_TOGGLE = ADC_ACK_PIN; // Tooggle ADC Data ACK
	}
}



