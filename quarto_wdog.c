/****************************************************************************
 ** wdog.c ******************************************************************
 ****************************************************************************
 *
 * Copyright (C) 2021, qNimble (https://qnimble.com)
 * Author: ben-qnimble
 *
 * Distributed under the GPL version 2.0.
 * See LICENSE for license details.
 */

#include "quarto_wdog.h"
#include "imxrt.h"
#include "gpio.h"

void quarto_wdog_init(uint16_t timeout) {
	if (timeout < 4) {
		timeout = 4;
	}

	__disable_irq();

	//Configure WDOG3 which will reboot if not fed
	WDOG3_CNT = 0xD928C520; //unlock watchdog
	while((WDOG3_CS & (WDOG_CS_ULK)) == 0); //wait until registers are unlocked
	WDOG3_TOVAL = timeout; //set timeout value
	WDOG3_CS = WDOG_CS_EN | WDOG_CS_CLK(1) | WDOG_CS_UPDATE | WDOG_CS_PRES | WDOG_CS_CMD32EN;
	while((WDOG3_CS & (WDOG_CS_RCS)) == 0); //wait until new configuration takes effect

	//Configure RTC Interrupt to interrupt and feed WDOG3

	// disable periodic interrupt
	SNVS_HPCR &= ~SNVS_HPCR_PI_EN;
	while ((SNVS_HPCR & SNVS_HPCR_PI_EN)) {} // spin until PI_EN is reset...

	SNVS_HPCR &= ~SNVS_HPCR_RTC_EN;
	while ((SNVS_HPCR & SNVS_HPCR_RTC_EN)) {} // spin until PI_EN is reset...

	// set interrupt frequency
	//0 = 32kHz, 1=16kHz, 2=8kHz..15 is 1Hz.

	uint8_t runat = 15; // default is 1 Hz.
	//if timeout greater than 512 tics of 128Hz clock (32.768kHz/256) or 4s, set runat to 1s
	//otherwise scale runat to give ~4 attempts before a WDOG3 reset
	while (timeout < 512) {
		timeout = timeout <<1; //make it twice as big.
		runat--;
		if (runat == 0) break;

	}


	SNVS_HPCR = SNVS_HPCR_PI_FREQ(runat);   // once per second, change for other frequencies (see IMXRT1062 manual for possible values)

	SNVS_HPCR |=  SNVS_HPCR_HPTA_EN | SNVS_HPCR_PI_EN ;
	SNVS_HPCR &=  ~SNVS_HPCR_DIS_PI ;

	SNVS_HPCR |=  SNVS_HPCR_RTC_EN ;

	while (!(SNVS_HPCR & SNVS_HPCR_RTC_EN)) {} // spin until PI_EN is set...
	while (!(SNVS_HPCR & SNVS_HPCR_PI_EN)) {} // spin until PI_EN is set...

	// attach a callback
	attachInterruptVector(IRQ_SNVS_IRQ, snvs_isr);
	NVIC_SET_PRIORITY(IRQ_SNVS_IRQ, 255);    // lowest priority
	NVIC_ENABLE_IRQ(IRQ_SNVS_IRQ);
	__enable_irq();

}

void snvs_isr(void) {
	SNVS_HPSR |= 0b11; // reset interrupt flag
	WDOG3_CNT = 0xB480A602; //Feed wdog3
	asm("dsb"); // wait until flag is synced over the busses to prevent double calls of the isr
}

void quarto_wdog_disable(void) {
	WDOG3_CNT = 0xB480A602; //Feed wdog3
	__disable_irq();
	WDOG3_CNT = 0xD928C520; //unlock watchdog

	while((WDOG3_CS & (WDOG_CS_ULK)) == 0); //wait until registers are unlocked

	WDOG3_CS &= ~WDOG_CS_EN;
	while((WDOG3_CS & (WDOG_CS_RCS)) == 0); //wait until reconfiguration done
	NVIC_DISABLE_IRQ(IRQ_SNVS_IRQ);
	__enable_irq();
}
