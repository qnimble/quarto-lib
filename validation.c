/****************************************************************************
 ** validation.c ************************************************************
 ****************************************************************************
 *
 * Copyright (C) 2021, qNimble (https://qnimble.com)
 * Author: ben-qnimble
 *
 * Distributed under the GPL version 2.0.
 * See LICENSE for license details.
 */

#include "validation.h"
#include "comm.h"
#include "printwrapper.h"
#include "core_pins.h"

bool testReadWrite(uint32_t seed,uint32_t* errors) {
	*errors = 0;
	bool success = true;
	uint16_t i;
	uint16_t data[DataTestSize];

	uint16_t startAddr = 0x50;
	uint16_t address = startAddr;
	uint16_t fakedata = seed*(seed+234)*(seed+24548);

	for(i=0;i<DataTestSize;i++) {
		fakedata += (fakedata+23)*(fakedata+317);
		data[i] = fakedata;
	}

	for(i=0;i<DataTestSize-startAddr;i++) {
		setWriteAddress(address++);
		writeData(data[i]);
	}


	serialprint("About to loop\r\n");
	address = startAddr;
	uint16_t temp;
	for(i=0;i<DataTestSize-startAddr;i++) {
		temp = readData(address);
		if (temp != data[i]) {
			success = false;
			printf("Error reading at 0x%08lx. Expecting 0x%04x but got 0x%04x\r\n",(uint32_t) address,data[i],temp);
			serialprint("Error reading at 0x");
			serialprintintashex(address);
			serialprint(" (i=");
			serialprintint(i);
			serialprint("). Expecting ");
			serialprintintashex(data[i]);
			serialprint(" but got ");
			serialprintintashex(temp);
			serialprint("\r\n");
			*errors = *errors +1;
		} else {
/*			serialprint("Success reading at 0x");
			serialprintintashex(address);
			serialprint(" (i=");
			serialprintint(i);
			serialprint("). Expecting ");
			serialprintintashex(data[i]);
			serialprint(" and got ");
			serialprintintashex(temp);
			serialprint("\r\n");
*/
		}
		address++;
		}

	printf("Test completed. i=%d, address=0x%04x and status is %d\r\n",i,address,success);
	return success;
}

