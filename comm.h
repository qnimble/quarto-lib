/*
 * comm.h
 *
 *  Created on: Oct 2, 2020
 *      Author: bluey
 */

#ifndef COMM_H_
#define COMM_H_

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

void setWriteAddress(uint16_t address);
void writeData(uint16_t data);
void QuartoInit(void);
uint16_t readData(uint16_t address);
uint8_t readReady(void);


#ifdef __cplusplus
}
#endif


#endif /* COMM_H_ */
