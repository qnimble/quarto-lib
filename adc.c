/****************************************************************************
 ** adc.c *******************************************************************
 ****************************************************************************
 *
 * Copyright (C) 2021, qNimble (https://qnimble.com)
 * Author: ben-qnimble
 *
 * Distributed under the GPL version 2.0.
 * See LICENSE for license details.
 */

#include "adc.h"
#include "comm.h"
#include "imxrt.h"
#include "pins_arduino.h"

static uint8_t _adc_scalemode[4] = {0,0,0,0};

void configureADC1(uint16_t fire_every_us, uint16_t fire_delay, adc_scale_t scale, void (*function)(void) ){
	NVIC_DISABLE_IRQ(ADC1_IRQ);
	_configureADC(1,fire_every_us,fire_delay,scale,function);
    _adc_scalemode[0] = 0x03 & ( ( ((uint8_t) scale))>>2) ;
	ADC1_IMR |= ADC1_BM;
	GPIO1_ICR1 &= ~ ( (0x2)<<(2*ADC1_PIN) );
	GPIO1_ICR1 |= ( (0x2)<<(2*ADC1_PIN) );
	attachInterruptVector(ADC1_IRQ, function);
	NVIC_SET_PRIORITY(ADC1_IRQ, 4);
	NVIC_ENABLE_IRQ(ADC1_IRQ);
}

void configureADC2(uint16_t fire_every_us, uint16_t fire_delay, adc_scale_t scale, void (*function)(void) ){
	NVIC_DISABLE_IRQ(ADC2_IRQ);
	_configureADC(2,fire_every_us,fire_delay,scale,function);
        _adc_scalemode[1] = 0x03 & ( ( ((uint8_t) scale))>>2) ;
	ADC2_IMR |= ADC2_BM;
	GPIO1_ICR1 &= ~ ( (0x2)<<(2*ADC2_PIN) );
	GPIO1_ICR1 |= ( (0x2)<<(2*ADC2_PIN) );
	attachInterruptVector(ADC2_IRQ, function);
	NVIC_SET_PRIORITY(ADC2_IRQ, 5);
	NVIC_ENABLE_IRQ(ADC2_IRQ);
}

void configureADC3(uint16_t fire_every_us, uint16_t fire_delay, adc_scale_t scale, void (*function)(void) ){
	NVIC_DISABLE_IRQ(ADC3_IRQ);
	_configureADC(3,fire_every_us,fire_delay,scale,function);
        _adc_scalemode[2] = 0x03 & ( ( ((uint8_t) scale))>>2) ;
	ADC3_IMR |= ADC3_BM;
	GPIO3_ICR1 &= ~ ( (0x2)<<(2*ADC3_PIN) );
	GPIO3_ICR1 |= ( (0x2)<<(2*ADC3_PIN) );
	attachInterruptVector(ADC3_IRQ, function);
	NVIC_SET_PRIORITY(ADC3_IRQ, 6);
	NVIC_ENABLE_IRQ(ADC3_IRQ);
}

void configureADC4(uint16_t fire_every_us, uint16_t fire_delay, adc_scale_t scale, void (*function)(void) ){
	NVIC_DISABLE_IRQ(ADC4_IRQ);
	_configureADC(4,fire_every_us,fire_delay,scale,function);
       _adc_scalemode[3] = 0x03 & ( ( ((uint8_t) scale))>>2) ;
	ADC4_IMR |= ADC4_BM;
	GPIO2_ICR2 &= ~ ( (0x2)<<(ADC4_PIN-1) );  //bit shift by 31*2 mod 32 is 30, or 31-1.
	GPIO2_ICR2 |= ( (0x2)<<(ADC4_PIN-1) );    //bit shift by 31*2 mod 32 is 30, or 31-1.
	attachInterruptVector(ADC4_IRQ, function);
	NVIC_SET_PRIORITY(ADC4_IRQ, 7);
	NVIC_ENABLE_IRQ(ADC4_IRQ);
}

void _configureADC(uint8_t channel,uint16_t fire_every_us, uint16_t fire_delay, adc_scale_t scale, void (*function)(void) ) {
	uint16_t range_addr;
	uint16_t adc_base_addr;
	switch(channel) {
		case 1:
			range_addr = ADC1_RANGE_ADDR;
			adc_base_addr = ADC1_BASE_ADDR;
			break;
		case 2:
			range_addr = ADC2_RANGE_ADDR;
			adc_base_addr = ADC2_BASE_ADDR;
			break;
		case 3:
			range_addr = ADC3_RANGE_ADDR;
			adc_base_addr = ADC3_BASE_ADDR;
			break;
		case 4:
			range_addr = ADC4_RANGE_ADDR;
			adc_base_addr = ADC4_BASE_ADDR;
			break;
		default:
			range_addr = 0;
            adc_base_addr = 0;
			break;
	}


	setWriteAddress(range_addr);
	writeData(scale);

	setWriteAddress(adc_base_addr + DELAY_FIRE_OFFSET);
	writeData(fire_delay);

	setWriteAddress(adc_base_addr + FIRE_EVERY_OFFSET);
	writeData(fire_every_us);
}

void disableADC1(void) {
	setWriteAddress(ADC1_BASE_ADDR + FIRE_EVERY_OFFSET);
	writeData(0);
	attachInterruptVector(ADC1_IRQ, adc1_irq_ignoredata);
}

void disableADC2(void) {
	setWriteAddress(ADC2_BASE_ADDR + FIRE_EVERY_OFFSET);
	writeData(0);
	attachInterruptVector(ADC2_IRQ, adc2_irq_ignoredata);
}

void disableADC3(void) {
	setWriteAddress(ADC3_BASE_ADDR + FIRE_EVERY_OFFSET);
	writeData(0);
	attachInterruptVector(ADC3_IRQ, adc3_irq_ignoredata);
}

void disableADC4(void) {
	setWriteAddress(ADC4_BASE_ADDR + FIRE_EVERY_OFFSET);
	writeData(0);
	attachInterruptVector(ADC4_IRQ, adc4_irq_ignoredata);
}


int16_t readADCRAW1_from_ISR(void) {
	GPIO1_ISR = ADC1_BM; // Clear Interrupt
	int16_t read = GPIO6_DR >> 16;
	GPIO6_DR_TOGGLE = 0x00000010; // Tooggle bootmode 0 as ACK
	return read;
}

double readADC1_from_ISR(void) {
	int32_t read = readADCRAW1_from_ISR();
	read = read << (_adc_scalemode[0]);
    double result = ADC_RAW_TO_VOLTAGE * read;
	return result;
}

int16_t readADCRAW2_from_ISR(void) {
	GPIO1_ISR = ADC2_BM; // Clear Interrupt
	int16_t read = GPIO6_DR >> 16;
	GPIO6_DR_TOGGLE = 0x00000010; // Tooggle bootmode 0 as ACK
	return read;
}

double readADC2_from_ISR(void) {
	int32_t read = readADCRAW2_from_ISR();
	read = read << (_adc_scalemode[1]);
    double result = ADC_RAW_TO_VOLTAGE * read;
	return result;
}



int16_t readADCRAW3_from_ISR(void) {
	GPIO3_ISR = ADC3_BM; // Clear Interrupt
	int16_t read = GPIO6_DR >> 16;
	GPIO6_DR_TOGGLE = 0x00000010; // Tooggle bootmode 0 as ACK
	return read;
}

double readADC3_from_ISR(void) {
	int32_t read = readADCRAW3_from_ISR();
	read = read << (_adc_scalemode[2]);
    double result = ADC_RAW_TO_VOLTAGE * read;
	return result;
}



int16_t readADCRAW4_from_ISR(void) {
	GPIO2_ISR = ADC4_BM; // Clear Interrupt
	int16_t read = GPIO6_DR >> 16;
	GPIO6_DR_TOGGLE = 0x00000010; // Tooggle bootmode 0 as ACK
	return read;
}

double readADC4_from_ISR(void) {
	int32_t read = readADCRAW4_from_ISR();
	read = read << (_adc_scalemode[3]);
    double result = ADC_RAW_TO_VOLTAGE * read;
	return result;
}

