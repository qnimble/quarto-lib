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
#include <stdbool.h>

#define SERIAL_NUMBER_ADDRESS 0x18004
#define HARDWARE_ID_ADDRESS 0x18008
#define HARDWARE_MAJOR_ADDRESS 0x1800A
#define HARDWARE_MINOR_ADDRESS 0x1800C
#define UUID_ADDRESS 0x18010

#define FIRMWARE_VERSION_ADDRESS 0x90
#define FIRMWARE_HWID_ADDRESS 0x91

#define LOOKUP_TABLE_START_CODE 0xFD23B500
#define LOOKUP_TABLE_END_CODE   0xEC12A400



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
void getHardwareUUID(uint8_t* uuid);
uint32_t getSerialNumber(void);
uint16_t getHardwareID(void);
uint16_t getHardwareMajorRev(void);
uint16_t getHardwareMinorRev(void);
uint16_t getFirmwareHWID(void);
uint16_t getFirmwareVersion(void);
uint8_t getFirmwareMajorRev(void);
uint16_t getFirmwareMinorRev(void);
uint16_t getFirmwarePatchRev(void);
char* getBootloaderRev(void);

#ifdef __cplusplus
	bool useExtClock(bool active, uint8_t trigger_pin = 1);
	bool useExtADCClock(bool active, uint8_t trigger_pin = 1);
#else
	bool useExtClock(bool active, uint8_t trigger_pin);
	bool useExtADCClock(bool active, uint8_t trigger_pin);
#endif

bool readExtClockEnabled(void);
bool readExtClockActive(void);

#ifdef __cplusplus
}
#endif


#endif /* COMM_H_ */
