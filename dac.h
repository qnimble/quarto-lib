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




#ifdef __cplusplus
extern "C" {
#endif

void zeroDACs(void);
void writeDAC1(int16_t data);
void writeDAC2(int16_t data);
void writeDAC3(int16_t data);
void writeDAC4(int16_t data);

#ifdef __cplusplus
}
#endif



#endif /* DAC_H_ */
