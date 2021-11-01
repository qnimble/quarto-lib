/*
 * printwrapper.cpp
 *
 *  Created on: May 4, 2021
 *      Author: bluey
 */


//#include "usb_serial.h"
#include "printwrapper.h"
#include "Arduino.h"


void serialprint(char* str) {
	Serial.print(str);
}

void serialprintint(uint32_t value) {
	Serial.print(value,DEC);
}

void serialprintintashex(uint32_t value) {
	Serial.print(value,HEX);
	//Serial.printf("%04x",value);
}
