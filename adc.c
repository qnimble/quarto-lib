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

void configureADC1(uint16_t fire_every_us, uint16_t fire_delay, adc_scale_t scale, void (*cb_function)(void) ){
	uint32_t ICR_temp;
	NVIC_DISABLE_IRQ(ADC1_IRQ);
	_configureADCSettings(1,fire_every_us,fire_delay,scale);
	_adc_scalemode[0] = 0x03 & ( ( ((uint8_t) scale))>>2) ;
	ADC1_IMR |= ADC1_BM;

#if ( ADC1_PIN < 16)
	ICR_temp = ADC1_ICR1;
	ICR_temp &= ~ ( (0x2)<<(2*ADC1_PIN) );
	ICR_temp |= ( (0x2)<<(2*ADC1_PIN) );
	ADC1_ICR1 = ICR_temp;
#else
	ICR_temp = ADC1_ICR2;
	ICR_temp &= ~ ( (0x2)<<(2*(ADC1_PIN-16)) );
	ICR_temp |= ( (0x2)<<(2*(ADC1_PIN-16)));
	ADC1_ICR2 = ICR_temp;
#endif

	attachInterruptVector(ADC1_IRQ, cb_function);
	NVIC_SET_PRIORITY(ADC1_IRQ, 0<<4);
	NVIC_ENABLE_IRQ(ADC1_IRQ);
}

void configureADC2(uint16_t fire_every_us, uint16_t fire_delay, adc_scale_t scale, void (*cb_function)(void) ){
	uint32_t ICR_temp;
	NVIC_DISABLE_IRQ(ADC2_IRQ);
	_configureADCSettings(2,fire_every_us,fire_delay,scale);
	_adc_scalemode[1] = 0x03 & ( ( ((uint8_t) scale))>>2) ;
	ADC2_IMR |= ADC2_BM;

#if ( ADC2_PIN < 16)
	ICR_temp = ADC2_ICR1;
	ICR_temp &= ~ ( (0x2)<<(2*ADC2_PIN) );
	ICR_temp |= ( (0x2)<<(2*ADC2_PIN) );
	ADC2_ICR1 = ICR_temp;
#else
	ICR_temp = ADC2_ICR2;
	ICR_temp &= ~ ( (0x2)<<(2*(ADC2_PIN-16)) );
	ICR_temp |= ( (0x2)<<(2*(ADC2_PIN-16)));
	ADC2_ICR2 = ICR_temp;
#endif
	attachInterruptVector(ADC2_IRQ, cb_function);
	NVIC_SET_PRIORITY(ADC2_IRQ, 1<<4);
	NVIC_ENABLE_IRQ(ADC2_IRQ);
}

void configureADC3(uint16_t fire_every_us, uint16_t fire_delay, adc_scale_t scale, void (*cb_function)(void) ){
	uint32_t ICR_temp;
	NVIC_DISABLE_IRQ(ADC3_IRQ);
	_configureADCSettings(3,fire_every_us,fire_delay,scale);
	_adc_scalemode[2] = 0x03 & ( ( ((uint8_t) scale))>>2) ;
	ADC3_IMR |= ADC3_BM;

#if ( ADC3_PIN < 16)
	ICR_temp = ADC3_ICR1;
	ICR_temp &= ~ ( (0x2)<<(2*ADC3_PIN) );
	ICR_temp |= ( (0x2)<<(2*ADC3_PIN) );
	ADC3_ICR1 = ICR_temp;
#else
	ICR_temp = ADC3_ICR2;
	ICR_temp &= ~ ( (0x2)<<(2*(ADC3_PIN-16)) );
	ICR_temp |= ( (0x2)<<(2*(ADC3_PIN-16)));
	ADC3_ICR2 = ICR_temp;
#endif

	attachInterruptVector(ADC3_IRQ, cb_function);
	NVIC_SET_PRIORITY(ADC3_IRQ, 2<<4);
	NVIC_ENABLE_IRQ(ADC3_IRQ);
}

void configureADC4(uint16_t fire_every_us, uint16_t fire_delay, adc_scale_t scale, void (*cb_function)(void) ){
	uint32_t ICR_temp;
	NVIC_DISABLE_IRQ(ADC4_IRQ);
	_configureADCSettings(4,fire_every_us,fire_delay,scale);
	_adc_scalemode[3] = 0x03 & ( ( ((uint8_t) scale))>>2) ;
	ADC4_IMR |= ADC4_BM;

#if ( ADC4_PIN < 16)
	ICR_temp = ADC4_ICR1;
	ICR_temp &= ~ ( (0x2)<<(2*ADC4_PIN) );
	ICR_temp |= ( (0x2)<<(2*ADC4_PIN) );
	ADC4_ICR1 = ICR_temp;
#else
	ICR_temp = ADC4_ICR2;
	ICR_temp &= ~ ( (0x2)<<(2*(ADC4_PIN-16)) );
	ICR_temp |= ( (0x2)<<(2*(ADC4_PIN-16)));
	ADC4_ICR2 = ICR_temp;
#endif

	attachInterruptVector(ADC4_IRQ, cb_function);
	NVIC_SET_PRIORITY(ADC4_IRQ, 3<<4);
	NVIC_ENABLE_IRQ(ADC4_IRQ);
}

void configureADC(uint8_t channel, uint16_t fire_every_us, uint16_t fire_delay, adc_scale_t scale, void (*cb_function)(void) ) {
	switch(channel) {
		case 1:
			configureADC1(fire_every_us,fire_delay,scale,cb_function);
			break;
		case 2:
			configureADC2(fire_every_us,fire_delay,scale,cb_function);
			break;
		case 3:
			configureADC3(fire_every_us,fire_delay,scale,cb_function);
			break;
		case 4:
			configureADC4(fire_every_us,fire_delay,scale,cb_function);
			break;
		default:
			break;
	}
}


void _configureADCSettings(uint8_t channel,uint16_t fire_every_us, uint16_t fire_delay, adc_scale_t scale ) {
	uint16_t range_addr;
	uint16_t adc_base_addr;

	if (fire_delay >= fire_every_us) {
		fire_delay = 0; //avoid setting delay greater than time between shots
	}

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


void disableADC(uint8_t channel) {
	switch(channel) {
		case 1:
			disableADC1();
			break;
		case 2:
			disableADC2();
			break;
		case 3:
			disableADC3();
			break;
		case 4:
			disableADC4();
			break;
		default:
			break;
	}
}




int16_t readADC1RAW_from_ISR(void) {
	ADC1_ISR = ADC1_BM; // Clear Interrupt
	int16_t read = GPIO6_DR >> 16;
	ADC_ACK_BANK_TOGGLE = ADC_ACK_PIN; // Tooggle bootmode 0 as ACK
	return read;
}

double readADC1_from_ISR(void) {
	int32_t read = readADC1RAW_from_ISR();
	read = read << (_adc_scalemode[0]);
    double result = ADC_RAW_TO_VOLTAGE * read;
	return result;
}

int16_t readADC2RAW_from_ISR(void) {
	ADC2_ISR = ADC2_BM; // Clear Interrupt
	int16_t read = GPIO6_DR >> 16;
	ADC_ACK_BANK_TOGGLE = ADC_ACK_PIN; // Tooggle bootmode 0 as ACK
	return read;
}

double readADC2_from_ISR(void) {
	int32_t read = readADC2RAW_from_ISR();
	read = read << (_adc_scalemode[1]);
    double result = ADC_RAW_TO_VOLTAGE * read;
	return result;
}



int16_t readADC3RAW_from_ISR(void) {
	ADC3_ISR = ADC3_BM; // Clear Interrupt
	int16_t read = GPIO6_DR >> 16;
	ADC_ACK_BANK_TOGGLE = ADC_ACK_PIN; // Tooggle bootmode 0 as ACK
	return read;
}

double readADC3_from_ISR(void) {
	int32_t read = readADC3RAW_from_ISR();
	read = read << (_adc_scalemode[2]);
    double result = ADC_RAW_TO_VOLTAGE * read;
	return result;
}



int16_t readADC4RAW_from_ISR(void) {
	ADC4_ISR = ADC4_BM; // Clear Interrupt
	int16_t read = GPIO6_DR >> 16;
	ADC_ACK_BANK_TOGGLE = ADC_ACK_PIN; // Tooggle bootmode 0 as ACK
	return read;
}

double readADC4_from_ISR(void) {
	int32_t read = readADC4RAW_from_ISR();
	read = read << (_adc_scalemode[3]);
	double result = ADC_RAW_TO_VOLTAGE * read;
	return result;
}

