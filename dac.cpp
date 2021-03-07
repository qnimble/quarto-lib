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
	writeDACRAW1(0);
	writeDACRAW2(0);
	writeDACRAW3(0);
	writeDACRAW4(0);
}

void writeDACRAW1(int16_t data) {
	asm volatile("nop\n");
	GPIO7_DR_TOGGLE = (0x00010000 + (uint16_t) data);

}

void writeDACRAW2(int16_t data) {
	asm volatile("nop\n");
	GPIO7_DR_TOGGLE = (0x00030000 + (uint16_t) data);

}

void writeDACRAW3(int16_t data) {
	asm volatile("nop\n");
	GPIO7_DR_TOGGLE = (0x00050000 + (uint16_t) data);

}

void writeDACRAW4(int16_t data) {
	asm volatile("nop\n");
	GPIO7_DR_TOGGLE = (0x00070000 + (uint16_t) data);

}


void writeDACRAW(int channel, int16_t data) {
	switch(channel) {
	case 1:
		GPIO7_DR_TOGGLE = (0x00010000 + (uint16_t) data);
		break;
	case 2:
		GPIO7_DR_TOGGLE = (0x00030000 + (uint16_t) data);
		break;
	case 3:
		GPIO7_DR_TOGGLE = (0x00050000 + (uint16_t) data);
		break;
	case 4:
		GPIO7_DR_TOGGLE = (0x00070000 + (uint16_t) data);
		break;
	default:
		break;
	}
}


void writeDAC1(float data) {
	int16_t dacvalue;
	if (data >= 10.2396875) dacvalue = 0x7FFF; //catch overflow
	else if (data <= -10.24) dacvalue = 0x8000; // catch underflow
	else dacvalue = (int16_t) ((data/10.24 * 32768) + 0.5 );
	GPIO7_DR_TOGGLE = (0x00010000 + (uint16_t) dacvalue);
}


void writeDAC1(double data) {
	int16_t dacvalue;
	if (data >= 10.2396875) dacvalue = 0x7FFF; //catch overflow
	else if (data <= -10.24) dacvalue = 0x8000; // catch underflow
	else dacvalue = (int16_t) ((data/10.24 * 32768) + 0.5 );
	GPIO7_DR_TOGGLE = (0x00010000 + (uint16_t) dacvalue);
}


void writeDAC2(float data) {
	int16_t dacvalue;
	if (data >= 10.2396875) dacvalue = 0x7FFF; //catch overflow
	else if (data <= -10.24) dacvalue = 0x8000; // catch underflow
	else dacvalue = (int16_t) ((data/10.24 * 32768) + 0.5 );
	GPIO7_DR_TOGGLE = (0x00030000 + (uint16_t) dacvalue);
}


void writeDAC2(double data) {
	int16_t dacvalue;
	if (data >= 10.2396875) dacvalue = 0x7FFF; //catch overflow
	else if (data <= -10.24) dacvalue = 0x8000; // catch underflow
	else dacvalue = (int16_t) ((data/10.24 * 32768) + 0.5 );
	GPIO7_DR_TOGGLE = (0x00030000 + (uint16_t) dacvalue);
}


void writeDAC3(float data) {
	int16_t dacvalue;
	if (data >= 10.2396875) dacvalue = 0x7FFF; //catch overflow
	else if (data <= -10.24) dacvalue = 0x8000; // catch underflow
	else dacvalue = (int16_t) ((data/10.24 * 32768) + 0.5 );
	GPIO7_DR_TOGGLE = (0x00050000 + (uint16_t) dacvalue);
}


void writeDAC3(double data) {
	int16_t dacvalue;
	if (data >= 10.2396875) dacvalue = 0x7FFF; //catch overflow
	else if (data <= -10.24) dacvalue = 0x8000; // catch underflow
	else dacvalue = (int16_t) ((data/10.24 * 32768) + 0.5 );
	GPIO7_DR_TOGGLE = (0x00050000 + (uint16_t) dacvalue);
}


void writeDAC4(float data) {
	int16_t dacvalue;
	if (data >= 10.2396875) dacvalue = 0x7FFF; //catch overflow
	else if (data <= -10.24) dacvalue = 0x8000; // catch underflow
	else dacvalue = (int16_t) ((data/10.24 * 32768) + 0.5 );
	GPIO7_DR_TOGGLE = (0x00070000 + (uint16_t) dacvalue);
}


void writeDAC4(double data) {
	int16_t dacvalue;
	if (data >= 10.2396875) dacvalue = 0x7FFF; //catch overflow
	else if (data <= -10.24) dacvalue = 0x8000; // catch underflow
	else dacvalue = (int16_t) ((data/10.24 * 32768) + 0.5 );
	GPIO7_DR_TOGGLE = (0x00070000 + (uint16_t) dacvalue);
}

void writeDAC(int channel, float data) {
	switch(channel) {
		case 1:
			writeDAC1(data);
			break;
		case 2:
			writeDAC2(data);
			break;
		case 3:
			writeDAC3(data);
			break;
		case 4:
			writeDAC4(data);
			break;
		default:
			break;
	}
}


void writeDAC(int channel, double data) {
	switch(channel) {
		case 1:
			writeDAC1(data);
			break;
		case 2:
			writeDAC2(data);
			break;
		case 3:
			writeDAC3(data);
			break;
		case 4:
			writeDAC4(data);
			break;
		default:
			break;
	}
}

