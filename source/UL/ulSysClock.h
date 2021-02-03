/*
 * ulSysClock.h
 *
 *  Created on: Feb 2, 2021
 *      Author: oleksandr.gonchar
 */

#ifndef UL_ULSYSCLOCK_H_
#define UL_ULSYSCLOCK_H_

#include <stdint.h>
#include <stdbool.h>

void ulSysClock_Init (void);

uint32_t ulSysClock_GetTime (void);

bool ulSysClock_IsTimePassed(uint32_t start_time, uint32_t period);

#endif /* UL_ULSYSCLOCK_H_ */
