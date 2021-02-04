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
