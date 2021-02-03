/*
 * halSysTick.h
 *
 *  Created on: Feb 1, 2021
 *      Author: oleksandr.gonchar
 */

#ifndef HAL_HALSYSTICK_H_
#define HAL_HALSYSTICK_H_

#include <stdint.h>

void halSysTick_Init (void);

uint32_t halSysTick_Get (void);

void SysTick_Handler(void);

#endif /* HAL_HALSYSTICK_H_ */
