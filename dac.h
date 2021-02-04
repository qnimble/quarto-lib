/****************************************************************************
 ** dac.h *******************************************************************
 ****************************************************************************
 *
 * Copyright (C) 2021, qNimble (https://qnimble.com)
 * Author: ben-qnimble
 *
 * Distributed under the GPL version 2.0.
 * See LICENSE for license details.
 */

#ifndef DAC_H_
#define DAC_H_

#include <stdint.h>
#include "imxrt.h"

#define writeDAC1(x) GPIO7_DR_TOGGLE = (0x00010000 + (uint16_t) (x))
#define writeDAC2(x) GPIO7_DR_TOGGLE = (0x00030000 + (uint16_t) (x))
#define writeDAC3(x) GPIO7_DR_TOGGLE = (0x00050000 + (uint16_t) (x))
#define writeDAC4(x) GPIO7_DR_TOGGLE = (0x00070000 + (uint16_t) (x))




#ifdef __cplusplus
extern "C" {
#endif

void zeroDACs(void);


#ifdef __cplusplus
}
#endif



#endif /* DAC_H_ */
