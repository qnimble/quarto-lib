/****************************************************************************
 ** gpio.cpp ****************************************************************
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
#include "core_pins.h"

void triggerMode(uint8_t pin, uint8_t mode) {
	switch (pin) {
	case 1:
		pinMode(12,mode);
		break;
	case 2:
		pinMode(13,mode);
		break;
	default:
		break;
	}
}


void triggerWrite(uint8_t pin, uint8_t value) {
	switch (pin) {
		case 1:
			digitalWrite(12,value);
			break;
		case 2:
			digitalWrite(13,value);
			break;
		default:
			break;
	}
}

uint8_t triggerRead(uint8_t pin) {
	switch (pin) {
		case 1:
			return digitalRead(12);
			break;
		case 2:
			return digitalRead(13);
			break;
		default:
			return 0;
			break;

	}
}


/*
void setTrigger1Direction(io_direction_t direction) {
	if (direction == PIN_DIRECTION_OUTPUT) {
		TRIGGER1_GDIR |= TRIGGER1_BM;
	} else {
		TRIGGER1_GDIR &= ~TRIGGER1_BM;
	}
}

void setTrigger2Direction(io_direction_t direction) {
	if (direction == PIN_DIRECTION_OUTPUT) {
		TRIGGER2_GDIR |= TRIGGER2_BM;
	} else {
		TRIGGER2_GDIR &= ~TRIGGER2_BM;
	}
}

void setTriggerDirection(uint8_t channel,io_direction_t direction) {
	switch(channel) {
	case 1:
		setTrigger1Direction(direction);
		break;
	case 2:
		setTrigger2Direction(direction);
		break;
	default:
		break;
	}
}
*/

void setLED(bool red, bool green, bool blue) {
    if (red) {
    	LED_BANK_DR_SET = LED_PIN_RED;
    } else {
    	LED_BANK_DR_CLEAR = LED_PIN_RED;
    }
    if (blue) {
    	LED_BANK_DR_SET = LED_PIN_BLUE;
    } else {
    	LED_BANK_DR_CLEAR = LED_PIN_BLUE;
    }
    if (green) {
    	LED_BANK_DR_SET = LED_PIN_GREEN;
    } else {
    	LED_BANK_DR_CLEAR = LED_PIN_GREEN;
    }
}

void toggleLED(bool red, bool green, bool blue) {
    if (red) {
    	LED_BANK_DR_TOGGLE = LED_PIN_RED;
    }
    if (blue) {
    	LED_BANK_DR_TOGGLE = LED_PIN_BLUE;
    }
    if (green) {
    	LED_BANK_DR_TOGGLE = LED_PIN_GREEN;
    }
}


void setLEDRed(bool on) {
	if (on) {
		LED_BANK_DR_SET = LED_PIN_RED;
	} else {
		LED_BANK_DR_CLEAR = LED_PIN_RED;
	}
}

void setLEDBlue(bool on) {
	if (on) {
		LED_BANK_DR_SET = LED_PIN_BLUE;
	} else {
		LED_BANK_DR_CLEAR = LED_PIN_BLUE;
	}
}

void setLEDGreen(bool on) {
	if (on) {
		LED_BANK_DR_SET = LED_PIN_GREEN;
	} else {
		LED_BANK_DR_CLEAR = LED_PIN_GREEN;
	}
}

void toggleLEDRed(void) {
	LED_BANK_DR_TOGGLE = LED_PIN_RED;
}

void toggleLEDGreen(void) {
	LED_BANK_DR_TOGGLE = LED_PIN_GREEN;
}

void toggleLEDBlue(void) {
	LED_BANK_DR_TOGGLE = LED_PIN_BLUE;
}

static void (*trigger1_IRQ)(void);
static void (*trigger2_IRQ)(void);

void enableInterruptTrigger1(trigger_edge_t edge, void (*cb_function)(void), unsigned int priority) {
	if (priority > 15) priority = 15;
	else priority = priority*16;

    trigger1_IRQ = cb_function;
	NVIC_DISABLE_IRQ(TRIGGER1_IRQ);
	TRIGGER1_IMR |= TRIGGER1_BM;

	if (edge == RISING_EDGE) {
		TRIGGER1_ICR1 &= ~ ( (0x3)<<(2*TRIGGER1_PIN) ); //mask off active bits
		TRIGGER1_ICR1 |= ( (0x2)<<(2*TRIGGER1_PIN) ); // set to 0x2
		TRIGGER1_EDGE_SEL &= ~(1<<TRIGGER1_PIN);
	} else if (edge == FALLING_EDGE) {
		TRIGGER1_ICR1 &= ~ ( (0x3)<<(2*TRIGGER1_PIN) );//mask off active bits
		TRIGGER1_ICR1 |= ( (0x3)<<(2*TRIGGER1_PIN) );  // set to 0x3
		TRIGGER1_EDGE_SEL &= ~(1<<TRIGGER1_PIN);
	} else if (edge == BOTH_EDGES) {
		TRIGGER1_EDGE_SEL |= (1<<TRIGGER1_PIN);
	}

	attachInterruptVector(TRIGGER1_IRQ, _intTrigger1);
	NVIC_SET_PRIORITY(TRIGGER1_IRQ, priority);
	NVIC_ENABLE_IRQ(TRIGGER1_IRQ);
}

void _intTrigger1(void) {
	TRIGGER1_ISR = TRIGGER1_BM;
    trigger1_IRQ();
     __asm__ volatile ("dsb");
}

void enableInterruptTrigger2(trigger_edge_t edge, void (*cb_function)(void), unsigned int priority) {
	if (priority > 15) priority = 15;
	else priority = priority*16;

    trigger2_IRQ = cb_function;
	NVIC_DISABLE_IRQ(TRIGGER2_IRQ);
	TRIGGER2_IMR |= TRIGGER2_BM;

	if (edge == RISING_EDGE) {
		TRIGGER2_ICR1 &= ~ ( (0x3)<<(2*TRIGGER2_PIN) );//mask off active bits
		TRIGGER2_ICR1 |= ( (0x2)<<(2*TRIGGER2_PIN) ); // set to 0x2
		TRIGGER2_EDGE_SEL &= ~(1<<TRIGGER2_PIN);
	} else if (edge == FALLING_EDGE ){
		TRIGGER2_ICR1 &= ~ ( (0x3)<<(2*TRIGGER2_PIN) ); //mask off active bits
		TRIGGER2_ICR1 |= ( (0x3)<<(2*TRIGGER2_PIN) );// set to 0x3
		TRIGGER2_EDGE_SEL &= ~(1<<TRIGGER2_PIN);
	} else {
		TRIGGER2_EDGE_SEL |= (1<<TRIGGER2_PIN);
	}


	attachInterruptVector(TRIGGER2_IRQ, _intTrigger2);
	NVIC_SET_PRIORITY(TRIGGER2_IRQ, priority);
	NVIC_ENABLE_IRQ(TRIGGER2_IRQ);
}

void enableInterruptTrigger(uint8_t pin, trigger_edge_t edge, void (*cb_function)(void), unsigned int priority) {
	switch (pin) {
		case 1:
			enableInterruptTrigger1(edge,cb_function,priority);
			break;
		case 2:
			enableInterruptTrigger2(edge,cb_function,priority);
			break;
		default:
			break;
	}
}

void enableInterruptTrigger(uint8_t pin, trigger_edge_t edge, void (*cb_function)(void)) {
	switch (pin) {
		case 1:
			enableInterruptTrigger1(edge,cb_function,4);
			break;
		case 2:
			enableInterruptTrigger2(edge,cb_function,5);
			break;
		default:
			break;
	}
}



void _intTrigger2(void) {
	TRIGGER2_ISR = TRIGGER2_BM;
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

void disableInterruptTrigger(uint8_t pin) {
	switch (pin) {
		case 1:
			disableInterruptTrigger1();
			break;
		case 2:
			disableInterruptTrigger2();
			break;
		default:
			break;
	}
}


