/*
 * validation.c
 *
 *  Created on: Nov 11, 2020
 *      Author: bluey
 */

#include "validation.h"
#include "comm.h"



bool testReadWrite(uint32_t seed) {
	bool success = true;
	uint16_t i;
	uint16_t data[DataTestSize];

	uint16_t startAddr = 0x50;
	uint16_t address = startAddr;
	uint16_t fakedata = seed*(seed+234);


	for(i=0;i<DataTestSize;i++) {
		fakedata += fakedata*(fakedata+317);
		data[i] = fakedata;
	}

	for(i=0;i<DataTestSize-startAddr;i++) {
		setWriteAddress(address++);
		writeData(data[i]);
	}

	address = startAddr;
	uint16_t temp;
	for(i=0;i<DataTestSize-startAddr;i++) {
		temp = readData(address);
		if (temp != data[i]) {
			success = false;
			printf("Error reading at 0x%08lx. Expecting 0x%04x but got 0x%04x\r\n",(uint32_t) address,data[i],temp);
		}
		address++;
		}


	printf("Test completed. i=%d, address=0x%04x and status is %d\r\n",i,address,success);
	return success;
}

