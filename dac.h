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

void writeDAC1(float data) ;
void writeDAC1(double data) ;

void zeroDACs(void);
void writeDACRAW1(int16_t data);
void writeDACRAW2(int16_t data);
void writeDACRAW3(int16_t data);
void writeDACRAW4(int16_t data);

void writeDACRAW(int channel, int16_t data);

void writeDAC1(float data);
void writeDAC1(double data);
void writeDAC2(float data);
void writeDAC2(double data);
void writeDAC3(float data);
void writeDAC3(double data);
void writeDAC4(float data);
void writeDAC4(double data);

void writeDAC(int channel, float data);
void writeDAC(int channel, double data);

#endif /* DAC_H_ */
