/*
 * blBlink.h
 *
 *  Created on: Feb 2, 2021
 *      Author: oleksandr.gonchar
 */

#ifndef BL_BLBLINK_H_
#define BL_BLBLINK_H_

#include <stdint.h>

void Blink_Init (uint32_t period);

void Blink_Run (void);

#endif /* BL_BLBLINK_H_ */
