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
		GPIO6_GDIR |= 0x02;
	} else {
		GPIO6_GDIR &= ~0x02;
	}
}

void setTrigger2Direction(int direction) {
	if (direction) {
		GPIO6_GDIR |= 0x01;
	} else {
		GPIO6_GDIR &= ~0x01;
	}
}


void setLED(bool red, bool green, bool blue) {
    if (red) {
        GPIO8_DR_SET = 0x01;
    } else {
        GPIO8_DR_CLEAR = 0x01;
    }
    if (blue) {
        GPIO8_DR_SET = 0x02;
    } else {
        GPIO8_DR_CLEAR = 0x02;
    }
    if (green) {
        GPIO8_DR_SET = 0x04;
    } else {
        GPIO8_DR_SET = 0x04;
    }
}

void toggleLED(bool red, bool green, bool blue) {
    if (red) {
        GPIO8_DR_TOGGLE = 0x01;
    }
    if (blue) {
        GPIO8_DR_TOGGLE = 0x02;
    }
    if (green) {
        GPIO8_DR_TOGGLE = 0x04;
    }
}
