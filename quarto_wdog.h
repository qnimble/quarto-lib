/****************************************************************************
 ** wdog.h ******************************************************************
 ****************************************************************************
 *
 * Copyright (C) 2021, qNimble (https://qnimble.com)
 * Author: ben-qnimble
 *
 * Distributed under the GPL version 2.0.
 * See LICENSE for license details.
 */

#ifndef QUARTO_WDOG_H_
#define QUARTO_WDOG_H_

#include <stdint.h>
#include "core_pins.h"
#define CRASHREPORT_HARDFAULT_APPLICATION 0xBADA0000
#define CRASHREPORT_HARDFAULT_BOOTLOADER  0xBADB0000
#define CRASHREPORT_RUN_APPLICATION  0xAABB0000
#define CRASHREPORT_APPLICATION_BOOTING  0xBBEE0000
#define CRASHREPORT_USB_REBOOT_SELECTED 0x1234ABCD




#ifdef __cplusplus
extern "C" {
#endif


void quarto_wdog_init(uint16_t timeout);
void snvs_isr(void);
void quarto_wdog_disable(void);
static inline void setDebugWord(uint32_t word) {SRC_GPR5 = word;};

#ifdef __cplusplus
}
#endif

#endif /* QUARTO_WDOG_H_ */
