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
	writeDAC1RAW(0);
	writeDAC2RAW(0);
	writeDAC3RAW(0);
	writeDAC4RAW(0);
}

void writeDAC1RAW(int16_t data) {
	GPIO2_DR_TOGGLE = (0x00010000 + (uint16_t) data);

}

void writeDAC2RAW(int16_t data) {
	GPIO2_DR_TOGGLE = (0x00030000 + (uint16_t) data);

}

void writeDAC3RAW(int16_t data) {
	GPIO2_DR_TOGGLE = (0x00050000 + (uint16_t) data);

}

void writeDAC4RAW(int16_t data) {
	GPIO2_DR_TOGGLE = (0x00070000 + (uint16_t) data);

}


void writeDACRAW(int channel, int16_t data) {
	switch(channel) {
	case 1:
		GPIO2_DR_TOGGLE = (0x00010000 + (uint16_t) data);
		break;
	case 2:
		GPIO2_DR_TOGGLE = (0x00030000 + (uint16_t) data);
		break;
	case 3:
		GPIO2_DR_TOGGLE = (0x00050000 + (uint16_t) data);
		break;
	case 4:
		GPIO2_DR_TOGGLE = (0x00070000 + (uint16_t) data);
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
	GPIO2_DR_TOGGLE = (0x00010000 + (uint16_t) dacvalue);
}


void writeDAC1(double voltage) {
	int16_t dacvalue;
	if (voltage >= 10.2396875) dacvalue = 0x7FFF; //catch overflow
	else if (voltage <= -10.24) dacvalue = 0x8000; // catch underflow
	else dacvalue = (int16_t) ((voltage/10.24 * 32768) + 0.5 );
	GPIO2_DR_TOGGLE = (0x00010000 + (uint16_t) dacvalue);
}

void writeDAC1(int voltage) {
	writeDAC1((float) voltage);
}


void writeDAC2(float voltage) {
	int16_t dacvalue;
	if (voltage >= 10.2396875) dacvalue = 0x7FFF; //catch overflow
	else if (voltage <= -10.24) dacvalue = 0x8000; // catch underflow
	else dacvalue = (int16_t) ((voltage/10.24 * 32768) + 0.5 );
	GPIO2_DR_TOGGLE = (0x00030000 + (uint16_t) dacvalue);
}


void writeDAC2(double voltage) {
	int16_t dacvalue;
	if (voltage >= 10.2396875) dacvalue = 0x7FFF; //catch overflow
	else if (voltage <= -10.24) dacvalue = 0x8000; // catch underflow
	else dacvalue = (int16_t) ((voltage/10.24 * 32768) + 0.5 );
	GPIO2_DR_TOGGLE = (0x00030000 + (uint16_t) dacvalue);
}

void writeDAC2(int voltage) {
	writeDAC2((float) voltage);
}


void writeDAC3(float voltage) {
	int16_t dacvalue;
	if (voltage >= 10.2396875) dacvalue = 0x7FFF; //catch overflow
	else if (voltage <= -10.24) dacvalue = 0x8000; // catch underflow
	else dacvalue = (int16_t) ((voltage/10.24 * 32768) + 0.5 );
	GPIO2_DR_TOGGLE = (0x00050000 + (uint16_t) dacvalue);
}


void writeDAC3(double voltage) {
	int16_t dacvalue;
	if (voltage >= 10.2396875) dacvalue = 0x7FFF; //catch overflow
	else if (voltage <= -10.24) dacvalue = 0x8000; // catch underflow
	else dacvalue = (int16_t) ((voltage/10.24 * 32768) + 0.5 );
	GPIO2_DR_TOGGLE = (0x00050000 + (uint16_t) dacvalue);
}

void writeDAC3(int voltage) {
	writeDAC3((float) voltage);
}


void writeDAC4(float voltage) {
	int16_t dacvalue;
	if (voltage >= 10.2396875) dacvalue = 0x7FFF; //catch overflow
	else if (voltage <= -10.24) dacvalue = 0x8000; // catch underflow
	else dacvalue = (int16_t) ((voltage/10.24 * 32768) + 0.5 );
	GPIO2_DR_TOGGLE = (0x00070000 + (uint16_t) dacvalue);
}


void writeDAC4(double voltage) {
	int16_t dacvalue;
	if (voltage >= 10.2396875) dacvalue = 0x7FFF; //catch overflow
	else if (voltage <= -10.24) dacvalue = 0x8000; // catch underflow
	else dacvalue = (int16_t) ((voltage/10.24 * 32768) + 0.5 );
	GPIO2_DR_TOGGLE = (0x00070000 + (uint16_t) dacvalue);
}

void writeDAC4(int voltage) {
	writeDAC4((float) voltage);
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

void writeDAC(int channel, int voltage) {
	writeDAC(channel,(float) voltage);
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

