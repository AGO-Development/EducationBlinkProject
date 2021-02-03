/*
 * dlLED.h
 *
 *  Created on: Feb 1, 2021
 *      Author: oleksandr.gonchar
 */

#ifndef DL_DLLED_H_
#define DL_DLLED_H_

#include <stdint.h>

typedef enum
{
  dlLED_Red,
  dlLED_Green,
  dlLED_Num
}dlLED_Type_t;

int8_t dlLED_Init (dlLED_Type_t led);

int8_t dlLED_On (dlLED_Type_t led);

int8_t dlLED_Off (dlLED_Type_t led);

int8_t dlLED_Toggle (dlLED_Type_t led);

#endif /* DL_DLLED_H_ */
