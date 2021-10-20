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
void _setNVMaddress(uint32_t address);
void _sendNVMdata(uint32_t data);
void writeData(uint16_t data);
void ClearDataRequests(void) ;
uint16_t readData(uint16_t address);
uint16_t readNVM(uint32_t address);
void readNVMblock(void* data,uint16_t length, uint32_t start_addr);
uint8_t readReady(void);
uint16_t writeAndRead(uint16_t address,uint16_t data);
int readStatus(void) ;
void writeNVMpages(void* data,uint16_t data_size, uint16_t first_page);

#ifdef __cplusplus
}
#endif


#endif /* COMM_H_ */
