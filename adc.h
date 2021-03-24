/****************************************************************************
 ** adc.h *******************************************************************
 ****************************************************************************
 *
 * Copyright (C) 2021, qNimble (https://qnimble.com)
 * Author: ben-qnimble
 *
 * Distributed under the GPL version 2.0.
 * See LICENSE for license details.
 */

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>
#include "imxrt.h"

typedef enum adc_scale {
	BIPOLAR_1250mV = 3,
	BIPOLAR_2500mV = 7,
	BIPOLAR_5V = 11,
	BIPOLAR_10V = 15
} __attribute__ ((__packed__)) adc_scale_t ;

#define ADC1_BASE_ADDR 0x030
#define ADC2_BASE_ADDR 0x032
#define ADC3_BASE_ADDR 0x034
#define ADC4_BASE_ADDR 0x036

#define FIRE_EVERY_OFFSET 0
#define DELAY_FIRE_OFFSET 1

#define ADC1_RANGE_ADDR 0x040
#define ADC2_RANGE_ADDR 0x041
#define ADC3_RANGE_ADDR 0x042
#define ADC4_RANGE_ADDR 0x043

#define ADC_RAW_TO_VOLTAGE 3.90625e-5


#ifdef __cplusplus
extern "C" {
#endif



extern void adc1_irq_ignoredata(void);
extern void adc2_irq_ignoredata(void);
extern void adc3_irq_ignoredata(void);
extern void adc4_irq_ignoredata(void);


void _configureADC(uint8_t channel,uint16_t fire_every_us, uint16_t fire_delay, adc_scale_t scale) ;

void configureADC1(uint16_t fire_every_us, uint16_t fire_delay, adc_scale_t scale, void (*cb_function)(void) );
void configureADC2(uint16_t fire_every_us, uint16_t fire_delay, adc_scale_t scale, void (*cb_function)(void) );
void configureADC3(uint16_t fire_every_us, uint16_t fire_delay, adc_scale_t scale, void (*cb_function)(void) );
void configureADC4(uint16_t fire_every_us, uint16_t fire_delay, adc_scale_t scale, void (*cb_function)(void) );

int16_t readADCRAW1_from_ISR(void);
int16_t readADCRAW2_from_ISR(void);
int16_t readADCRAW3_from_ISR(void);
int16_t readADCRAW4_from_ISR(void);

double readADC1_from_ISR(void);
double readADC2_from_ISR(void);
double readADC3_from_ISR(void);
double readADC4_from_ISR(void);


void disableADC1(void);
void disableADC2(void);
void disableADC3(void);
void disableADC4(void);

#ifdef __cplusplus
}
#endif

#endif /* ADC_H_ */
