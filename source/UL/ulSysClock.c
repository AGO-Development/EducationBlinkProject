/*
 * ulSysClock.c
 *
 *  Created on: Feb 2, 2021
 *      Author: oleksandr.gonchar
 */

#include "ulSysClock.h"
#include "../HAL/halSysTick.h"
#include <stdint.h>

void ulSysClock_Init (void)
{
  halSysTick_Init();
}

uint32_t ulSysClock_GetTime (void)
{
  return halSysTick_Get();
}

bool ulSysClock_IsTimePassed(uint32_t start_time, uint32_t period)
{
  uint32_t passedTime = 0;

  passedTime = ulSysClock_GetTime() - start_time;

  return (passedTime >= period);
}
