/*
 * blBlink.c
 *
 *  Created on: Feb 2, 2021
 *      Author: oleksandr.gonchar
 */

#include "blBlink.h"
#include "../DL/dlLED.h"
#include "../UL/ulSysClock.h"

static uint32_t blink_period = 500; // Default 500 ms

void Blink_Init (uint32_t period)
{
  dlLED_Init(dlLED_Green);
  blink_period = period;
}

void Blink_Run ()
{
  static uint32_t time = 0;

  if (ulSysClock_IsTimePassed(time, blink_period))
  {
    dlLED_Toggle(dlLED_Green);
    time = ulSysClock_GetTime();
  }
}
