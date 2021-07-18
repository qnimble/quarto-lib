/*
 * printwrapper.h
 *
 *  Created on: May 4, 2021
 *      Author: bluey
 */

#ifndef PRINTWRAPPER_H_
#define PRINTWRAPPER_H_


#include <stdint.h>




#ifdef __cplusplus
extern "C" {
#endif


void serialprint(char* str);
void serialprintint(uint32_t value);
void serialprintintashex(uint32_t value);



#ifdef __cplusplus
}
#endif


#endif /* PRINTWRAPPER_H_ */
