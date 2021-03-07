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
        GPIO8_DR_SET = LED_PIN_RED;
    } else {
        GPIO8_DR_CLEAR = LED_PIN_RED;
    }
    if (blue) {
        GPIO8_DR_SET = LED_PIN_BLUE;
    } else {
        GPIO8_DR_CLEAR = LED_PIN_BLUE;
    }
    if (green) {
        GPIO8_DR_SET = LED_PIN_GREEN;
    } else {
        GPIO8_DR_CLEAR = LED_PIN_GREEN;
    }
}

void toggleLED(bool red, bool green, bool blue) {
    if (red) {
        GPIO8_DR_TOGGLE = LED_PIN_RED;
    }
    if (blue) {
        GPIO8_DR_TOGGLE = LED_PIN_BLUE;
    }
    if (green) {
        GPIO8_DR_TOGGLE = LED_PIN_GREEN;
    }
}


void setLEDRed(bool on) {
	if (on) {
		GPIO8_DR_SET = LED_PIN_RED;
	} else {
		GPIO8_DR_CLEAR = LED_PIN_RED;
	}
}

void setLEDBlue(bool on) {
	if (on) {
		GPIO8_DR_SET = LED_PIN_BLUE;
	} else {
		GPIO8_DR_CLEAR = LED_PIN_BLUE;
	}
}

void setLEDGreen(bool on) {
	if (on) {
		GPIO8_DR_SET = LED_PIN_GREEN;
	} else {
		GPIO8_DR_CLEAR = LED_PIN_GREEN;
	}
}

void toggleLEDRed(void) {
	GPIO8_DR_TOGGLE = LED_PIN_RED;
}

void toggleLEDGreen(void) {
	GPIO8_DR_TOGGLE = LED_PIN_GREEN;
}

void toggleLEDBlue(void) {
	GPIO8_DR_TOGGLE = LED_PIN_BLUE;
}

