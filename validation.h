/*
 * validation.h
 *
 *  Created on: Nov 11, 2020
 *      Author: bluey
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
