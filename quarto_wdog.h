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



#ifdef __cplusplus
extern "C" {
#endif


void quarto_wdog_init(uint16_t timeout);
void snvs_isr(void);
void quarto_wdog_disable(void);


#ifdef __cplusplus
}
#endif

#endif /* QUARTO_WDOG_H_ */
