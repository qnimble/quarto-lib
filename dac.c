/****************************************************************************
 ** dac.c *******************************************************************
 ****************************************************************************
 *
 * Copyright (C) 2021, qNimble (https://qnimble.com)
 * Author: ben-qnimble
 *
 * Distributed under the GPL version 2.0.
 * See LICENSE for license details.
 */

#include "dac.h"

void zeroDACs(void) {
	writeDAC1(0);
	writeDAC2(0);
	writeDAC3(0);
	writeDAC4(0);
}

void writeDAC1(int16_t data) {
	GPIO7_DR_TOGGLE = (0x00010000 + (uint16_t) data);
	asm volatile("nop\n");
}

void writeDAC2(int16_t data) {
	GPIO7_DR_TOGGLE = (0x00030000 + (uint16_t) data);
	asm volatile("nop\n");
}

void writeDAC3(int16_t data) {
	GPIO7_DR_TOGGLE = (0x00050000 + (uint16_t) data);
	asm volatile("nop\n");
}

void writeDAC4(int16_t data) {
	GPIO7_DR_TOGGLE = (0x00070000 + (uint16_t) data);
	asm volatile("nop\n");
}
