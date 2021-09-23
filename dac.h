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

void zeroDACs(void);

void writeDACRAW1(int16_t data);
void writeDACRAW2(int16_t data);
void writeDACRAW3(int16_t data);
void writeDACRAW4(int16_t data);

void writeDACRAW(int channel, int16_t data);

void writeDAC1(float voltage);
void writeDAC1(double voltage);
void writeDAC2(float voltage);
void writeDAC2(double voltage);
void writeDAC3(float voltage);
void writeDAC3(double voltage);
void writeDAC4(float voltage);
void writeDAC4(double voltage);

void writeDAC(int channel, float voltage);
void writeDAC(int channel, double voltage);

float readDAC(int channel);
int16_t readDACRAW(int channel);

#endif /* DAC_H_ */
