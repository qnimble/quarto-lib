/****************************************************************************
 ** gpio.h ******************************************************************
 ****************************************************************************
 *
 * Copyright (C) 2021, qNimble (https://qnimble.com)
 * Author: ben-qnimble
 *
 * Distributed under the GPL version 2.0.
 * See LICENSE for license details.
 */

#ifndef GPIO_H_
#define GPIO_H_

#include <stdbool.h>
#include "imxrt.h"

#define LED_PIN_RED 0x01
#define LED_PIN_BLUE 0x02
#define LED_PIN_GREEN 0x04

#define LED_BANK_DR_SET GPIO8_DR_SET
#define LED_BANK_DR_CLEAR GPIO8_DR_CLEAR
#define LED_BANK_DR_TOGGLE GPIO8_DR_TOGGLE

#define TRIGGER1_PIN 1
#define TRIGGER2_PIN 0

#define TRIGGER1_BM (1<<(TRIGGER1_PIN))
#define TRIGGER2_BM (1<<(TRIGGER2_PIN))

#define TRIGGER1_GDIR GPIO6_GDIR
#define TRIGGER2_GDIR GPIO6_GDIR

#define TRIGGER1_ISR GPIO1_ISR
#define TRIGGER2_ISR GPIO1_ISR

#define TRIGGER1_IMR GPIO1_IMR
#define TRIGGER2_IMR GPIO1_IMR

#define TRIGGER1_ICR1 GPIO1_ICR1
#define TRIGGER2_ICR1 GPIO1_ICR1

#define TRIGGER1_EDGE_SEL GPIO1_EDGE_SEL
#define TRIGGER2_EDGE_SEL GPIO1_EDGE_SEL


#define TRIGGER1_IRQ IRQ_GPIO1_INT1
#define TRIGGER2_IRQ IRQ_GPIO1_INT0

typedef enum io_direction {
	PIN_DIRECTION_OUTPUT = 1,
	PIN_DIRECTION_INPUT = 0
} __attribute__ ((__packed__)) io_direction_t ;

typedef enum trigger_edge {
    FALLING_EDGE = 0,
	RISING_EDGE = 1,
	BOTH_EDGES = 2,
} __attribute__ ((__packed__)) trigger_edge_t ;



void setTrigger1Direction(io_direction_t direction);
void setTrigger2Direction(io_direction_t direction);
void triggerMode(uint8_t pin, uint8_t mode);
void triggerWrite(uint8_t pin, uint8_t value);
uint8_t triggerRead(uint8_t pin);
void triggerToggle(uint8_t pin);
void setTriggerDirection(uint8_t channel,io_direction_t direction);
void setLED(bool red, bool green, bool blue);
void toggleLED(bool red, bool green, bool blue);

void setLEDRed(bool on);
void setLEDGreen(bool on);
void setLEDBlue(bool on);
void toggleLEDRed(void);
void toggleLEDGreen(void);
void toggleLEDBlue(void);




#ifdef __cplusplus
	void enableInterruptTrigger1(trigger_edge_t edge, void (*cb_function)(void), unsigned int priority = 2);
	void enableInterruptTrigger2(trigger_edge_t edge, void (*cb_function)(void), unsigned int priority = 3);
	void enableInterruptTrigger(uint8_t pin, trigger_edge_t edge, void (*cb_function)(void));
	void enableInterruptTrigger(uint8_t pin, trigger_edge_t edge, void (*cb_function)(void), unsigned int priority);
extern "C" {
#else
	void enableInterruptTrigger1(bool rising_edge, void (*cb_function)(void), unsigned int priority);
	void enableInterruptTrigger2(bool rising_edge, void (*cb_function)(void), unsigned int priority);
	void enableInterruptTrigger(uint8_t pin, trigger_edge_t edge, void (*cb_function)(void), unsigned int priority);
#endif




static inline void setTrigger1High(void) __attribute__((always_inline, unused));
static inline void setTrigger1High(void) {
	GPIO6_DR_SET = 0x02;
}

static inline void setTrigger1Low(void) __attribute__((always_inline, unused));
static inline void setTrigger1Low(void) {
	GPIO6_DR_CLEAR = 0x02;
}

static inline void setTrigger2High(void) __attribute__((always_inline, unused));
static inline void setTrigger2High(void) {
	GPIO6_DR_SET = 0x01;
}

static inline void setTrigger2Low(void) __attribute__((always_inline, unused));
static inline void setTrigger2Low(void) {
	GPIO6_DR_CLEAR = 0x01;
}

void _intTrigger1(void);
void _intTrigger2(void);


static inline bool getTrigger1(void) __attribute__((always_inline, unused));
static inline bool getTrigger1(void) {
	return ((GPIO1_DR & TRIGGER1_BM) == TRIGGER1_BM);
}

static inline bool getTrigger2(void) __attribute__((always_inline, unused));
static inline bool getTrigger2(void) {
	return ((GPIO1_DR & TRIGGER2_BM) == TRIGGER2_BM);
}

void disableInterruptTrigger1(void);
void disableInterruptTrigger2(void);
void disableInterruptTrigger(uint8_t pin);



#ifdef __cplusplus
}
#endif

#endif /* GPIO_H_ */
