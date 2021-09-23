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
#include "comm.h"

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


void writeDAC1(float voltage) {
	int16_t dacvalue;
	if (voltage >= 10.2396875) dacvalue = 0x7FFF; //catch overflow
	else if (voltage <= -10.24) dacvalue = 0x8000; // catch underflow
	else dacvalue = (int16_t) ((voltage/10.24 * 32768) + 0.5 );
	GPIO7_DR_TOGGLE = (0x00010000 + (uint16_t) dacvalue);
}


void writeDAC1(double voltage) {
	int16_t dacvalue;
	if (voltage >= 10.2396875) dacvalue = 0x7FFF; //catch overflow
	else if (voltage <= -10.24) dacvalue = 0x8000; // catch underflow
	else dacvalue = (int16_t) ((voltage/10.24 * 32768) + 0.5 );
	GPIO7_DR_TOGGLE = (0x00010000 + (uint16_t) dacvalue);
}


void writeDAC2(float voltage) {
	int16_t dacvalue;
	if (voltage >= 10.2396875) dacvalue = 0x7FFF; //catch overflow
	else if (voltage <= -10.24) dacvalue = 0x8000; // catch underflow
	else dacvalue = (int16_t) ((voltage/10.24 * 32768) + 0.5 );
	GPIO7_DR_TOGGLE = (0x00030000 + (uint16_t) dacvalue);
}


void writeDAC2(double voltage) {
	int16_t dacvalue;
	if (voltage >= 10.2396875) dacvalue = 0x7FFF; //catch overflow
	else if (voltage <= -10.24) dacvalue = 0x8000; // catch underflow
	else dacvalue = (int16_t) ((voltage/10.24 * 32768) + 0.5 );
	GPIO7_DR_TOGGLE = (0x00030000 + (uint16_t) dacvalue);
}


void writeDAC3(float voltage) {
	int16_t dacvalue;
	if (voltage >= 10.2396875) dacvalue = 0x7FFF; //catch overflow
	else if (voltage <= -10.24) dacvalue = 0x8000; // catch underflow
	else dacvalue = (int16_t) ((voltage/10.24 * 32768) + 0.5 );
	GPIO7_DR_TOGGLE = (0x00050000 + (uint16_t) dacvalue);
}


void writeDAC3(double voltage) {
	int16_t dacvalue;
	if (voltage >= 10.2396875) dacvalue = 0x7FFF; //catch overflow
	else if (voltage <= -10.24) dacvalue = 0x8000; // catch underflow
	else dacvalue = (int16_t) ((voltage/10.24 * 32768) + 0.5 );
	GPIO7_DR_TOGGLE = (0x00050000 + (uint16_t) dacvalue);
}


void writeDAC4(float voltage) {
	int16_t dacvalue;
	if (voltage >= 10.2396875) dacvalue = 0x7FFF; //catch overflow
	else if (voltage <= -10.24) dacvalue = 0x8000; // catch underflow
	else dacvalue = (int16_t) ((voltage/10.24 * 32768) + 0.5 );
	GPIO7_DR_TOGGLE = (0x00070000 + (uint16_t) dacvalue);
}


void writeDAC4(double voltage) {
	int16_t dacvalue;
	if (voltage >= 10.2396875) dacvalue = 0x7FFF; //catch overflow
	else if (voltage <= -10.24) dacvalue = 0x8000; // catch underflow
	else dacvalue = (int16_t) ((voltage/10.24 * 32768) + 0.5 );
	GPIO7_DR_TOGGLE = (0x00070000 + (uint16_t) dacvalue);
}

void writeDAC(int channel, float voltage) {
	switch(channel) {
		case 1:
			writeDAC1(voltage);
			break;
		case 2:
			writeDAC2(voltage);
			break;
		case 3:
			writeDAC3(voltage);
			break;
		case 4:
			writeDAC4(voltage);
			break;
		default:
			break;
	}
}


void writeDAC(int channel, double voltage) {
	switch(channel) {
		case 1:
			writeDAC1(voltage);
			break;
		case 2:
			writeDAC2(voltage);
			break;
		case 3:
			writeDAC3(voltage);
			break;
		case 4:
			writeDAC4(voltage);
			break;
		default:
			break;
	}
}


int16_t readDACRAW(int channel) {
    uint16_t address = 0x24;
    switch(channel) {
      case 2:
        address += 1;
        break;
      case 3:
        address += 2;
        break;
      case 4:
          address += 3;
          break;
      default:
        break;
    }
  int16_t res = ( int16_t) readData(address);
  return res;
}


float readDAC(int channel) {
	int16_t dacvalue = readDACRAW(channel) ;
	return  0.0003125*dacvalue ;
}

