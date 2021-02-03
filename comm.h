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
uint16_t writeAndRead(uint16_t address,uint16_t data);
void writeDAC1(int16_t data);
void writeDAC2(int16_t data);
void writeDAC3(int16_t data);
void writeDAC4(int16_t data);
void zeroDACs(void);
int readStatus(void) ;


#ifdef __cplusplus
}
#endif


#endif /* COMM_H_ */
