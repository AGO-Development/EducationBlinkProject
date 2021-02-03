/*
 * dlButton.c
 *
 *  Created on: Feb 1, 2021
 *      Author: oleksandr.gonchar
 */

#include "dlButton.h"

#include "../HAL/halGPIO.h"
#include "../UL/ulError.h"
#include "../UL/ulSysClock.h"

#include <stddef.h>

#define DL_BUTTON_DEBOUNCE_COUNT_MAX 100
#define DL_BUTTON_DEBOUNCE_COUNT_MIN 5
#define DL_BUTTON_RUN_PERIOD_1MS     1

typedef struct dlButton_descr
{
  halGPIO_descr_t*  pin_instance;
  halGPIO_Config_t  pin_config;
  dlButton_state_t  pin_state_last;
  uint32_t          debounce_counter;
  ptr_event_handler callback_click;
}dlButton_descr_t;

static dlButton_descr_t joystick[dlButtonNum] =
{
    {NULL, {halGPIO_Port_0, halGPIO_Pin_0, halGPIO_Mode_In, halGPIO_Pull_Down}, dlButton_Released, 0, NULL},
    {NULL, {halGPIO_Port_0, halGPIO_Pin_1, halGPIO_Mode_In, halGPIO_Pull_Down}, dlButton_Released, 0, NULL},
    {NULL, {halGPIO_Port_0, halGPIO_Pin_2, halGPIO_Mode_In, halGPIO_Pull_Down}, dlButton_Released, 0, NULL},
    {NULL, {halGPIO_Port_0, halGPIO_Pin_5, halGPIO_Mode_In, halGPIO_Pull_Down}, dlButton_Released, 0, NULL},
    {NULL, {halGPIO_Port_0, halGPIO_Pin_3, halGPIO_Mode_In, halGPIO_Pull_Down}, dlButton_Released, 0, NULL}
};

static void update_buttons (void);
static void debounce_button (dlButton_descr_t * ptr_button);

int8_t dlButton_Init (dlButton_t type, ptr_event_handler callback)
{
  int8_t error = ulError_NULL;

  joystick[type].pin_instance     = halGPIO_Pin_Init(joystick[type].pin_config);
  joystick[type].debounce_counter = DL_BUTTON_DEBOUNCE_COUNT_MIN;
  joystick[type].callback_click   = callback;

  if (joystick[type].pin_instance != NULL)
  {
    error = ulError_OK;
  }
  return error;
}

void dlButton_Run (void)
{
  static uint32_t time = 0;

  if (ulSysClock_IsTimePassed(time, DL_BUTTON_RUN_PERIOD_1MS))
  {
    update_buttons();
    time = ulSysClock_GetTime();
  }
}

void update_buttons (void)
{
  for (uint8_t i = 0; i < dlButtonNum; i++)
  {
    if (joystick[i].pin_instance != NULL)
    {
      debounce_button(&joystick[i]);

      if ((joystick[i].debounce_counter == DL_BUTTON_DEBOUNCE_COUNT_MAX) && (joystick[i].pin_state_last == dlButton_Released))
      {
	joystick[i].pin_state_last = dlButton_Pressed;
      }
      else if ((joystick[i].debounce_counter == DL_BUTTON_DEBOUNCE_COUNT_MIN) && (joystick[i].pin_state_last == dlButton_Pressed))
      {
	joystick[i].pin_state_last = dlButton_Released;
	if (joystick[i].callback_click != NULL)
	{
	  joystick[i].callback_click();
	}
      }
    }
  }
}

void debounce_button (dlButton_descr_t * ptr_button)
{
  if ((ptr_button != NULL) && (ptr_button->pin_instance != NULL))
  {
    if (halGPIO_Pin_Get(ptr_button->pin_instance) == halGPIO_Pin_High)
    {
      ptr_button->debounce_counter++;
    }
    else
    {
      ptr_button->debounce_counter--;
    }

    if (ptr_button->debounce_counter > DL_BUTTON_DEBOUNCE_COUNT_MAX)
    {
      ptr_button->debounce_counter = DL_BUTTON_DEBOUNCE_COUNT_MAX;
    }

    if (ptr_button->debounce_counter < DL_BUTTON_DEBOUNCE_COUNT_MIN)
    {
      ptr_button->debounce_counter = DL_BUTTON_DEBOUNCE_COUNT_MIN;
    }
  }
}
