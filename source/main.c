/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

#include "DL/dlButton.h"
#include "DL/dlLED.h"
#include "UL/ulSysClock.h"
#include "BL/blBlink.h"

void toggle(void)
{
  dlLED_Toggle(dlLED_Red);
}

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  ulSysClock_Init();

  dlLED_Init(dlLED_Red);
  dlButton_Init(dlButtonSelect, &toggle);
  dlButton_Init(dlButtonLeft, &toggle);
  dlButton_Init(dlButtonRight, &toggle);
  dlButton_Init(dlButtonDown, &toggle);
  dlButton_Init(dlButtonUp, &toggle);

  Blink_Init(100);

  while (1)
  {
    dlButton_Run();
    Blink_Run();
  }
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
