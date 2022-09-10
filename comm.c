/****************************************************************************
 ** comm.c ******************************************************************
 ****************************************************************************
 *
 * Copyright (C) 2021, qNimble (https://qnimble.com)
 * Author: ben-qnimble
 *
 * Distributed under the GPL version 2.0.
 * See LICENSE for license details.
 */


#include "imxrt.h"
#include "comm.h"
#include "pins_arduino.h"
#include "core_pins.h"

static int _status = 0;

void setWriteAddress(uint16_t address) {
	GPIO2_DR_TOGGLE = (0x000B0000 + address);
}

void writeData(uint16_t data) {
	GPIO2_DR_TOGGLE = (0x000D0000 + data);
}

uint16_t writeAndRead(uint16_t address,uint16_t data){
	setWriteAddress(address);
	writeData(data);
	uint16_t loops = 0;
	uint16_t result;
	do {
		result = readData(address);
		loops++;
		if (loops >= 10) {
			_status++;
			return 0xFFFE;
		}
	} while ( result != data);
	
	return result;
}


void _setNVMaddress(uint32_t address) {
	uint8_t upper_byte = address>>24;
	setWriteAddress(0x3000 + upper_byte);

	uint16_t middle_part = ((address>>12) & 0x0FFF);
	setWriteAddress(0x2000 + middle_part);

	uint16_t lowest = ((address) & 0x0FFF);
	setWriteAddress(0x1000 + lowest);

}


uint16_t readData(uint16_t address) {
	//GPIO6_DR_SET = 0x02;
	uint full_loops = 0;
	while(1) {
		GPIO2_DR_TOGGLE = (0x000F0000 + address);
		uint i = 0;
		while(readReady() == 0) { //Wait until data ready
			i++;
			if (i > 300){
				//printf("Read failed on address=0x%04x, re-trying\r\n",address);
				goto final;
			}
		}
		uint16_t read = GPIO6_DR >> 16;

		if ( readReady() == 0 ) {
			//Read no longer valid, (ADC data came in), retry
			goto final;
		}

		READDATA_ACK_BANK_TOGGLE = READDATA_ACK_PIN; // Toggle Read Data ACK

		i=0;
		while(readReady() == 1) { //Wait until data read has been acknowledged
			//printf("Waiting for data read to be ACKd (attempt %d without retoggle)...\r\n",i);
			i++;
			if (i%10==0){
				//printf("Failed to get ack of read, toggling again\r\n");
				READDATA_ACK_BANK_TOGGLE = READDATA_ACK_PIN; // Tooggle bootmode 1
			}
			if (i > 100){
				//printf("Giving up on read, moving on\r\n");
				//Serial.println("Giving up on read, moving on");
				_status++;
				//GPIO6_DR_CLEAR = 0x02;
				return 0;
			}
		}
		//GPIO6_DR_CLEAR = 0x02;

		//printf(" of @0x%04x\r\n",read);
		return read;

		final:
			full_loops++;
			if (full_loops > 10) {
				_status++;
				//GPIO6_DR_CLEAR = 0x02;
				return 0;
			}
			continue;
	}
}


int readStatus(void) {
	return _status;
}


uint8_t readReady(void){
	if ((READDATA_READY_BANK & READDATA_READY_PIN) == READDATA_READY_PIN ){
		return 1;
	} else
		return 0;
}


uint16_t readNVM(uint32_t address) {
	if (address >= 0x20000) {
		_status = 14;
		return 0; //128kB of EEPROM, stop if address too large
	}
	_setNVMaddress(0x60000000 + address);
	return readData(0x1000);
}


void readNVMblock(void* data,uint16_t length, uint32_t start_addr) {
	uint16_t reads = (length+1)/2;
	uint16_t read_data;
	uint8_t* read_data_ptr;
	uint8_t* data_ptr = data;
	for(uint16_t i = 0; i < reads; i++) {
		read_data_ptr = (uint8_t*) &read_data;
		read_data = readNVM(start_addr + 2*i);
		*data_ptr++ = *read_data_ptr++;
		length--;
		if (length != 0 ) {
			*data_ptr++ = *read_data_ptr++;
		}
	}
}



uint32_t getSerialNumber(void) {
	uint32_t serial_number;
	readNVMblock(&serial_number,sizeof(serial_number),SERIAL_NUMBER_ADDRESS);
	return serial_number;
}

uint16_t getHardwareID(void) {
	return readNVM(HARDWARE_ID_ADDRESS);
}


uint16_t getHardwareMajorRev(void) {
	return readNVM(HARDWARE_MAJOR_ADDRESS);
}

uint16_t getHardwareMinorRev(void) {
	return readNVM(HARDWARE_MINOR_ADDRESS);
}

uint16_t getFirmwareVersion(void) {
	return readData(FIRMWARE_VERSION_ADDRESS);
}

uint16_t getFirmwareHWID(void) {
	return readData(FIRMWARE_HWID_ADDRESS);
}

uint8_t getFirmwareMajorRev(void) {
	return (getFirmwareHWID() & 0x8000) == 0x8000;
}

uint16_t getFirmwareMinorRev(void) {
	return getFirmwareHWID() & ~0x8000;
}

uint16_t getFirmwarePatchRev(void) {
	return getFirmwareVersion();
}


char* getBootloaderRev(void) {
  uint32_t* data_ptr = (uint32_t*) 0x60000800;
  if (*data_ptr == LOOKUP_TABLE_START_CODE) {
    /*
    char* str_ptr = (char*) *(data_ptr + 1);
    Serial.printf("Full Bootloader Version is %s",str_ptr);
    str_ptr = (char*)  *(data_ptr + 2);
    Serial.printf("Version of bootloader info is %s\n",(str_ptr));
    Serial.printf("Flash Size: 0x%08x\n",*(data_ptr+3));
    Serial.printf("End Code: 0x%08x\n",*(data_ptr+4));
    */
    return (char*) *(data_ptr + 2);
  } else {
    return NULL;
  }
}


void getHardwareUUID(uint8_t* uuid) {
	readNVMblock(uuid,sizeof(uint32_t)*4,UUID_ADDRESS);
	return;
}





void writeNVMpages(void* data,uint16_t data_size, uint16_t start_page) {
	_status = 0;
	uint32_t NV_FREQRNG_orig;

	if (data_size == 0) {
		_status = 20;
		return;
	} else if ( data_size + start_page*128 >= 131072) {
		_status = 21; //size plus starting page outside 128kB size of EEPROM
		return;
	}

	_setNVMaddress(0x600801FC); // REQACCESS register
	_sendNVMdata(0x01); //request exclusive eNVM access
	uint16_t result = readData(0x1000); //read from same memory address
	if (( result & 0x04 ) != 0x04) { // check that we got exclusive access
		_status = 15;
		return;
	}

	_setNVMaddress(0x60080158); // CLRHINT register
	_sendNVMdata(0x03); //Clear errors

	_setNVMaddress(0x4003800C); // ENVM_CR  register
	NV_FREQRNG_orig = readData(0x1000);

	_sendNVMdata(NV_FREQRNG_orig | 0x01E0); //SET NV_FREQRNG to 0xF, per chip eratta

	_setNVMaddress(0x6008012C); // NV_FREQRNG read-only register

	result = readData(0x1000); //read
	if (( result ) != 0xF) { //Make sure NV_FREQRNG = 0xF
		_status = 17;
		return;
	}

	uint8_t bytes_to_write;
	uint8_t bytes_to_zero;
	uint32_t* data_32 = (uint32_t*) data;

	while(data_size > 0) {
		if (data_size >= 128){
			bytes_to_write=128;
			bytes_to_zero = 0;
			data_size -= 128;
		} else {
			bytes_to_write = data_size;
			bytes_to_zero = 128 - data_size;
			data_size = 0;
		}

		uint32_t WDB_Reg = 0x60080080;
		uint32_t temp_data;
		uint8_t* temp_ptr;
		while(bytes_to_write > 0) {
			_setNVMaddress(WDB_Reg); // WDB register
			WDB_Reg += 4;
			if (bytes_to_write >=4 ) {
				_sendNVMdata(*data_32++);
				bytes_to_write -= 4;
			} else {
				temp_data = *data_32; //bad data at end since bytes to write less than 4
				temp_ptr = (uint8_t*) &temp_data;
				for(uint8_t i=0;i<4;i++) {
					if ( bytes_to_write != 0) {
						bytes_to_write--;
						temp_ptr++;
					} else {
						*temp_ptr++ = 0x00; //zero out remaining bits
						bytes_to_zero--;
					}
				}
				_sendNVMdata(temp_data);
			}
		}
		while(bytes_to_zero > 0) {
			if ((bytes_to_zero & 0x3) != 0) {
				//bytes_to_zero should be divisibe by 4, first two bits zero
				_status = 22;
				return;
			}

			_setNVMaddress(WDB_Reg); // WDB register
			WDB_Reg += 4;
			_sendNVMdata(0);
			bytes_to_zero -= 4;
		}

		//do unlock
		_setNVMaddress(0x60D80148); // CMD  register
		uint32_t unlock = 0x05000000;
		_sendNVMdata(unlock); //do wr


		//loading full page with data
		_setNVMaddress(0x60080148); // CMD  register
		uint32_t payload = 0x08000000;
		payload +=  ((128*start_page++) & 0x3FF80) ; //set page by masking addresses lowest 7 bits (and bits above 17 to keep in eNVM space)
		_sendNVMdata(payload); //do write

		uint loops = 0;
		while(1) {
			_setNVMaddress(0x60080120); // status register
			result = readData(0x1000); //read from same spot

			if (( result & 0x01) == 0x01) {
				break; // break out of loop once NVM to completes task
			}

			if (loops > 10000) {
				_status = 18; //timeout on eNVM completion
				return;
			}

			delayMicroseconds(25);
			loops++;
		}
	}

	_setNVMaddress(0x4003800C); // REQACCESS register
	_sendNVMdata(NV_FREQRNG_orig); //SET NV_FREQRNG back to original value

	_setNVMaddress(0x600801FC); // REQACCESS register
	_sendNVMdata(00); //release exclusive access
}



void _sendNVMdata(uint32_t data) {
	uint8_t thirdbyte = (data>> 16) & 0x00FF;
	setWriteAddress(0x4000 + thirdbyte);
	uint8_t fourthbyte = (data >> 24) & 0x00FF;
	setWriteAddress(0x5000 + fourthbyte);
	uint16_t lowerhalf = data;
	GPIO2_DR_TOGGLE = (0x000D0000 + lowerhalf);
}



void ClearDataRequests(void) {
	for(int i=0;i<16;i++) {
		READDATA_ACK_BANK_TOGGLE = READDATA_ACK_PIN; // Toggle Read Data ACK
		ADC_ACK_BANK_TOGGLE = ADC_ACK_PIN; // Tooggle ADC Data ACK
	}
}


bool useExtClock(bool active) {
  uint16_t output;
  output = readData(0x010); //read current settings
  if (active) {
	  output |= 0x10; //set bit to enable external clock
  } else {
	  output &= ~0x10; //clear bit to disable external clock
  }
  setWriteAddress(0x010); //Set Write address to 0x010 for updating settings
  writeData(output); //Set new settings to enable external clock
  return readExtClockEnabled();
}

bool readExtClockEnabled(void) {
  uint16_t output = readData(0x010) ; //read current settings
  return output & 0x10;
}

bool readExtClockActive(void) {
  uint16_t data = readData(0x09F); //read ext clock status
  if ( data == 02 ) return 1;
  else return 0;
}
