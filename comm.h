/*
 * comm.h
 *
 *  Created on: Oct 2, 2020
 *      Author: bluey
 */

#ifndef COMM_H_
#define COMM_H_

#include <stdio.h>


#define ADC1_BM 0x00000004
#define ADC2_BM 0x00000008
#define ADC3_BM 0x00000200
#define ADC4_BM 0x80000000

#define ADC1_IOBANK GPIO6_DR
#define ADC2_IOBANK GPIO6_DR
#define ADC3_IOBANK GPIO6_DR
#define ADC4_IOBANK GPIO7_DR

#ifdef __cplusplus
extern "C" {
#endif

void setWriteAddress(uint16_t address);
void writeData(uint16_t data);
void QuartoInit(void);
uint16_t readData(uint16_t address);
uint8_t readReady(void);
uint16_t writeAndRead(uint16_t address,uint16_t data);
void writeDAC1(uint16_t data);
void writeDAC2(uint16_t data);
void writeDAC3(uint16_t data);
void writeDAC4(uint16_t data);
int16_t readADC(void);
void zeroDACs(void);

#ifdef __cplusplus
}
#endif


#endif /* COMM_H_ */
