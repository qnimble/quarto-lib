/*
 * adc.h
 *
 *  Created on: Jan 28, 2021
 *      Author: bluey
 */

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>

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


#define ADC1_PIN 2
#define ADC2_PIN 3
#define ADC3_PIN 4
#define ADC4_PIN 31


#define ADC1_BM (1<<(ADC1_PIN))
#define ADC2_BM (1<<(ADC2_PIN))
#define ADC3_BM (1<<(ADC3_PIN))
#define ADC4_BM (1<<(ADC4_PIN))

#define ADC1_IOBANK GPIO6_DR
#define ADC2_IOBANK GPIO6_DR
#define ADC3_IOBANK GPIO8_DR
#define ADC4_IOBANK GPIO7_DR




#ifdef __cplusplus
extern "C" {
#endif


void configureADC(uint8_t channel,uint16_t fire_every_us, uint16_t fire_delay, adc_scale_t scale, void (*function)(void) ) ;

void configureADC1(uint16_t fire_every_us, uint16_t fire_delay, adc_scale_t scale, void (*function)(void) );
void configureADC2(uint16_t fire_every_us, uint16_t fire_delay, adc_scale_t scale, void (*function)(void) );
void configureADC3(uint16_t fire_every_us, uint16_t fire_delay, adc_scale_t scale, void (*function)(void) );
void configureADC4(uint16_t fire_every_us, uint16_t fire_delay, adc_scale_t scale, void (*function)(void) );

int16_t readADC1_from_ISR(void);
int16_t readADC2_from_ISR(void);
int16_t readADC3_from_ISR(void);
int16_t readADC4_from_ISR(void);

void disableADC1(void);
void disableADC2(void);
void disableADC3(void);
void disableADC4(void);


#ifdef __cplusplus
}
#endif


#endif /* ADC_H_ */
