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


void setTrigger1Direction(io_direction_t direction) {
	if (direction == PIN_DIRECTION_OUTPUT) {
		GPIO6_GDIR |= TRIGGER1_BM;
	} else {
		GPIO6_GDIR &= ~TRIGGER1_BM;
	}
}

void setTrigger2Direction(io_direction_t direction) {
	if (direction == PIN_DIRECTION_OUTPUT) {
		GPIO6_GDIR |= TRIGGER2_BM;
	} else {
		GPIO6_GDIR &= ~TRIGGER2_BM;
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

static void (*trigger1_IRQ)(void);
static void (*trigger2_IRQ)(void);

void enableInterruptTrigger1(bool rising_edge, void (*cb_function)(void), unsigned int priority) {
	if (priority > 15) priority = 15;
	else priority = priority*16;

        trigger1_IRQ = cb_function;
	NVIC_DISABLE_IRQ(TRIGGER1_IRQ);
	TRIGGER1_IMR |= TRIGGER1_BM;

	if (rising_edge) {
		GPIO1_ICR1 &= ~ ( (0x2)<<(2*TRIGGER1_PIN) );
		GPIO1_ICR1 |= ( (0x2)<<(2*TRIGGER1_PIN) );
	} else {
		GPIO1_ICR1 &= ~ ( (0x3)<<(2*TRIGGER1_PIN) );
		GPIO1_ICR1 |= ( (0x3)<<(2*TRIGGER1_PIN) );
	}

	attachInterruptVector(TRIGGER1_IRQ, _intTrigger1);
	NVIC_SET_PRIORITY(TRIGGER1_IRQ, priority);
	NVIC_ENABLE_IRQ(TRIGGER1_IRQ);
}

void _intTrigger1(void) {
    GPIO1_ISR = TRIGGER1_BM;
    trigger1_IRQ();
     __asm__ volatile ("dsb");
}

void enableInterruptTrigger2(bool rising_edge, void (*cb_function)(void), unsigned int priority) {
	if (priority > 15) priority = 15;
	else priority = priority*16;

        trigger2_IRQ = cb_function;
	NVIC_DISABLE_IRQ(TRIGGER2_IRQ);
	TRIGGER2_IMR |= TRIGGER2_BM;

	if (rising_edge) {
		GPIO1_ICR2 &= ~ ( (0x2)<<(2*TRIGGER2_PIN) );
		GPIO1_ICR2 |= ( (0x2)<<(2*TRIGGER2_PIN) );
	} else {
		GPIO1_ICR2 &= ~ ( (0x3)<<(2*TRIGGER2_PIN) );
		GPIO1_ICR2 |= ( (0x3)<<(2*TRIGGER2_PIN) );
	}

	attachInterruptVector(TRIGGER2_IRQ, _intTrigger2);
	NVIC_SET_PRIORITY(TRIGGER2_IRQ, priority);
	NVIC_ENABLE_IRQ(TRIGGER2_IRQ);
}

void _intTrigger2(void) {
    GPIO1_ISR = TRIGGER2_BM;
    trigger2_IRQ();
     __asm__ volatile ("dsb");
}

void disableInterruptTrigger1(void) {
	NVIC_DISABLE_IRQ(TRIGGER1_IRQ);
	TRIGGER1_IMR &= ~TRIGGER1_BM;
}

void disableInterruptTrigger2(void) {
	NVIC_DISABLE_IRQ(TRIGGER2_IRQ);
	TRIGGER2_IMR &= ~TRIGGER2_BM;
}
