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

static int _status = 0;

void setWriteAddress(uint16_t address) {
	GPIO7_DR_TOGGLE = (0x000B0000 + address);
}

void writeData(uint16_t data) {
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

uint16_t readData(uint16_t address) {	
	GPIO6_DR_SET = 0x02;
	uint full_loops = 0;
	while(1) {
		GPIO7_DR_TOGGLE = (0x000F0000 + address);
		uint i = 0;
		while(readReady() == 0) { //Wait until data ready
			i++;
			if (i > 10){
				//printf("Read failed on address=0x%04x, re-trying\r\n",address);
				goto final;
			}
		}
		uint16_t read = GPIO6_DR >> 16;

		if ( readReady() == 0 ) {
			//Read no longer valid, (ADC data came in), retry
			goto final;
		}

		GPIO6_DR_TOGGLE = 0x00000020; // Toggle Read Data ACK

		i=0;
		while(readReady() == 1) { //Wait until data read has been acknowledged
			//printf("Waiting for data read to be ACKd (attempt %d without retoggle)...\r\n",i);
			i++;
			if (i%10==0){
				//printf("Failed to get ack of read, toggling again\r\n");				
				GPIO6_DR_TOGGLE = 0x00000020; // Tooggle bootmode 1
			}
			if (i > 100){
				//printf("Giving on read, moving on\r\n");
				//Serial.println("Giving up on read, moving on");
				_status++;
				GPIO6_DR_CLEAR = 0x02;
				return 0;
			}
		}
		GPIO6_DR_CLEAR = 0x02;

		//printf(" of @0x%04x\r\n",read);
		return read;

		final:
			full_loops++;
			if (full_loops > 10) {
				_status++;
				GPIO6_DR_CLEAR = 0x02;
				return 0;
			}
			continue;
	}
}


int readStatus(void) {
	return _status;
}


uint8_t readReady(void){
	if ((GPIO6_DR & 0x0200) == 0x0200 ){
		return 1;
	} else
		return 0;
}

void ClearDataRequests(void) {
	for(int i=0;i<16;i++) {
		GPIO6_DR_TOGGLE = 0x00000020; // Toggle Read Data ACK
		GPIO6_DR_TOGGLE = 0x00000010; // Tooggle ADC Data ACK
	}
}



