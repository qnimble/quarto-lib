/****************************************************************************
 ** comm.h ******************************************************************
 ****************************************************************************
 *
 * Copyright (C) 2021, qNimble (https://qnimble.com)
 * Author: ben-qnimble
 *
 * Distributed under the GPL version 2.0.
 * See LICENSE for license details.
 */

#ifndef COMM_H_
#define COMM_H_

#include <stdio.h>


#ifdef __cplusplus
extern "C" {
#endif

void setWriteAddress(uint16_t address);
void writeData(uint16_t data);
void ClearDataRequests(void) ;
uint16_t readData(uint16_t address);
uint16_t readEEPROM(uint32_t address);
uint8_t readReady(void);
uint16_t writeAndRead(uint16_t address,uint16_t data);
int readStatus(void) ;


#ifdef __cplusplus
}
#endif


#endif /* COMM_H_ */
