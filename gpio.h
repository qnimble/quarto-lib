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

#define PIN_DIRECTION_OUTPUT 1
#define PIN_DIRECTION_INPUT 0


#ifdef __cplusplus
extern "C" {
#endif

void setTrigger1Direction(int direction);
void setTrigger2Direction(int direction);



#define setTrigger1High() GPIO6_DR_SET = 0x02
#define setTrigger1Low() GPIO6_DR_CLEAR = 0x02
#define setTrigger2High() GPIO6_DR_SET = 0x01
#define setTrigger2Low() GPIO6_DR_CLEAR = 0x01


#ifdef __cplusplus
}
#endif


#endif /* GPIO_H_ */
