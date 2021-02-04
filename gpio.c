/****************************************************************************
 ** gpio.c ******************************************************************
 ****************************************************************************
 *
 * Copyright (C) 2021, qNimble (https://qnimble.com)
 * Author: ben-qnimble
 *
 * Distributed under the GPL version 2.0.
 * See LICENSE for license details.
 */


#include "gpio.h"
#include "imxrt.h"


void setTrigger1Direction(int direction) {
	if (direction) {
		GPIO6_GDIR |= 0x01;
	} else {
		GPIO6_GDIR &= ~0x01;
	}
}

void setTrigger2Direction(int direction) {
	if (direction) {
		GPIO6_GDIR |= 0x02;
	} else {
		GPIO6_GDIR &= ~0x02;
	}
}


