/*
 * gpio.c
 *
 *  Created on: Jan 20, 2021
 *      Author: bluey
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


