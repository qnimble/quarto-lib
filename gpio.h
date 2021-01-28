/*
 * gpio.h
 *
 *  Created on: Jan 20, 2021
 *      Author: bluey
 */

#ifndef GPIO_H_
#define GPIO_H_

#define PIN_DIRECTION_OUTPUT 1
#define PIN_DIRECTION_INPUT 0


#ifdef __cplusplus
extern "C" {
#endif

void setTrigger1Direction(int direction);
void setTrigger2Direction(int direction);



#define setTrigger1High() GPIO6_DR_SET = 0x01
#define setTrigger1Low() GPIO6_DR_CLEAR = 0x01
#define setTrigger2High() GPIO6_DR_SET = 0x02
#define setTrigger2Low() GPIO6_DR_CLEAR = 0x02


#ifdef __cplusplus
}
#endif


#endif /* GPIO_H_ */
