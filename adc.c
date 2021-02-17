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

void configureADC1(uint16_t fire_every_us, uint16_t fire_delay, adc_scale_t scale, void (*function)(void) ){
	NVIC_DISABLE_IRQ(ADC1_IRQ);
	configureADC(1,fire_every_us,fire_delay,scale,function);
	ADC1_IMR |= ADC1_BM;
	GPIO1_ICR1 &= ~ ( (0x2)<<(2*ADC1_PIN) );
	GPIO1_ICR1 |= ( (0x2)<<(2*ADC1_PIN) );
	attachInterruptVector(ADC1_IRQ, function);
	NVIC_SET_PRIORITY(ADC1_IRQ, 4);
	NVIC_ENABLE_IRQ(ADC1_IRQ);
}

void configureADC2(uint16_t fire_every_us, uint16_t fire_delay, adc_scale_t scale, void (*function)(void) ){
	NVIC_DISABLE_IRQ(ADC2_IRQ);
	configureADC(2,fire_every_us,fire_delay,scale,function);
	ADC2_IMR |= ADC2_BM;
	GPIO1_ICR1 &= ~ ( (0x2)<<(2*ADC2_PIN) );
	GPIO1_ICR1 |= ( (0x2)<<(2*ADC2_PIN) );
	attachInterruptVector(ADC2_IRQ, function);
	NVIC_SET_PRIORITY(ADC2_IRQ, 5);
	NVIC_ENABLE_IRQ(ADC2_IRQ);
}

void configureADC3(uint16_t fire_every_us, uint16_t fire_delay, adc_scale_t scale, void (*function)(void) ){
	NVIC_DISABLE_IRQ(ADC3_IRQ);
	configureADC(3,fire_every_us,fire_delay,scale,function);
	ADC3_IMR |= ADC3_BM;
	GPIO3_ICR1 &= ~ ( (0x2)<<(2*ADC3_PIN) );
	GPIO3_ICR1 |= ( (0x2)<<(2*ADC3_PIN) );
	attachInterruptVector(ADC3_IRQ, function);
	NVIC_SET_PRIORITY(ADC3_IRQ, 6);
	NVIC_ENABLE_IRQ(ADC3_IRQ);
}

void configureADC4(uint16_t fire_every_us, uint16_t fire_delay, adc_scale_t scale, void (*function)(void) ){
	NVIC_DISABLE_IRQ(ADC4_IRQ);
	configureADC(4,fire_every_us,fire_delay,scale,function);
	ADC4_IMR |= ADC4_BM;
	GPIO2_ICR2 &= ~ ( (0x1)<<(ADC4_PIN-1) );  //bit shift by 31*2 mod 32 is 30, or 31-1.
	GPIO2_ICR2 |= ( (0x1)<<(ADC4_PIN-1) );    //bit shift by 31*2 mod 32 is 30, or 31-1.
	attachInterruptVector(ADC4_IRQ, function);
	NVIC_SET_PRIORITY(ADC4_IRQ, 7);
	NVIC_ENABLE_IRQ(ADC4_IRQ);
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


void configureADC(uint8_t channel,uint16_t fire_every_us, uint16_t fire_delay, adc_scale_t scale, void (*function)(void) ) {
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



int16_t readADC1_from_ISR(void) {
	GPIO1_ISR = ADC1_BM; // Clear Interrupt
	int16_t read = GPIO6_DR >> 16;
	GPIO6_DR_TOGGLE = 0x00000010; // Tooggle bootmode 0 as ACK
	return read;
}

int16_t readADC2_from_ISR(void) {
	GPIO1_ISR = ADC2_BM; // Clear Interrupt
	int16_t read = GPIO6_DR >> 16;
	GPIO6_DR_TOGGLE = 0x00000010; // Tooggle bootmode 0 as ACK
	return read;
}

int16_t readADC3_from_ISR(void) {
	GPIO3_ISR = ADC3_BM; // Clear Interrupt
	int16_t read = GPIO6_DR >> 16;
	GPIO6_DR_TOGGLE = 0x00000010; // Tooggle bootmode 0 as ACK
	return read;
}

int16_t readADC4_from_ISR(void) {
	GPIO2_ISR = ADC4_BM; // Clear Interrupt
	int16_t read = GPIO6_DR >> 16;
	GPIO6_DR_TOGGLE = 0x00000010; // Tooggle bootmode 0 as ACK
	return read;
}


