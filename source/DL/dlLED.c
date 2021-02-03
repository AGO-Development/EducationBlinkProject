/*
 * dlLED.c
 *
 *  Created on: Feb 1, 2021
 *      Author: oleksandr.gonchar
 */

#include "dlLED.h"

#include "../HAL/halGPIO.h"
#include "../UL/ulError.h"

#include <stddef.h>

typedef struct dlLED_descr
{
  halGPIO_descr_t*  pin_instance;
  halGPIO_Config_t  pin_config;
}dlLED_descr_t;

static dlLED_descr_t leds[dlLED_Num] =
{
  {NULL, {halGPIO_Port_1, halGPIO_Pin_2, halGPIO_Mode_Out, halGPIO_Pull_NoPull}},
  {NULL, {halGPIO_Port_4, halGPIO_Pin_8, halGPIO_Mode_Out, halGPIO_Pull_NoPull}}
};

int8_t dlLED_Init (dlLED_Type_t led)
{
  int8_t error = ulError_NULL;

  leds[led].pin_instance = halGPIO_Pin_Init(leds[led].pin_config);

  if (leds[led].pin_instance != NULL)
  {
    error = ulError_OK;
  }
  return error;
}

int8_t dlLED_On (dlLED_Type_t led)
{
  return halGPIO_Pin_Set(leds[led].pin_instance);
}

int8_t dlLED_Off (dlLED_Type_t led)
{
  return halGPIO_Pin_Reset(leds[led].pin_instance);
}

int8_t dlLED_Toggle (dlLED_Type_t led)
{
  if (halGPIO_Pin_Get(leds[led].pin_instance) == halGPIO_Pin_Low)
  {
    return dlLED_On(led);
  }
  else
  {
    return dlLED_Off(led);
  }
}
