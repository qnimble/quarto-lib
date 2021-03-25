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

#define PIN_DIRECTION_OUTPUT 1
#define PIN_DIRECTION_INPUT 0

#define LED_PIN_RED 0x01
#define LED_PIN_BLUE 0x02
#define LED_PIN_GREEN 0x04


#define TRIGGER1_PIN 1
#define TRIGGER2_PIN 0

#define TRIGGER1_BM (1<<(TRIGGER1_PIN))
#define TRIGGER2_BM (1<<(TRIGGER2_PIN))

#define TRIGGER1_ISR GPIO1_ISR
#define TRIGGER2_ISR GPIO1_ISR

#define TRIGGER1_IMR GPIO1_IMR
#define TRIGGER2_IMR GPIO1_IMR

#define TRIGGER1_IRQ IRQ_GPIO1_INT1
#define TRIGGER2_IRQ IRQ_GPIO1_INT0




void setTrigger1Direction(int direction);
void setTrigger2Direction(int direction);
void setLED(bool red, bool green, bool blue);
void toggleLED(bool red, bool green, bool blue);

void setLEDRed(bool on);
void setLEDGreen(bool on);
void setLEDBlue(bool on);
void toggleLEDRed(void);
void toggleLEDGreen(void);
void toggleLEDBlue(void);


#define setTrigger1High() GPIO6_DR_SET = 0x02
#define setTrigger1Low() GPIO6_DR_CLEAR = 0x02
#define setTrigger2High() GPIO6_DR_SET = 0x01
#define setTrigger2Low() GPIO6_DR_CLEAR = 0x01

#define clearISRTrigger1() GPIO1_ISR = TRIGGER1_BM; // Clear Interrupt
#define clearISRTrigger2() GPIO1_ISR = TRIGGER1_BM; // Clear Interrupt



void enableInterruptTrigger1(bool rising_edge, void (*cb_function)(void), unsigned int priority = 4);
void enableInterruptTrigger2(bool rising_edge, void (*cb_function)(void), unsigned int priority = 5);
void disableInterruptTrigger1(void);
void disableInterruptTrigger2(void);




#endif /* GPIO_H_ */
