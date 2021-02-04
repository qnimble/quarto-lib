/****************************************************************************
 ** validation.h ************************************************************
 ****************************************************************************
 *
 * Copyright (C) 2021, qNimble (https://qnimble.com)
 * Author: ben-qnimble
 *
 * Distributed under the GPL version 2.0.
 * See LICENSE for license details.
 */


#ifndef VALIDATION_H_
#define VALIDATION_H_

#define DataTestSize 1024

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>



bool testReadWrite(uint32_t seed);

#ifdef __cplusplus
}
#endif


#endif /* VALIDATION_H_ */
