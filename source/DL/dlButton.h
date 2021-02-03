/*
 * dlButtton.h
 *
 *  Created on: Feb 1, 2021
 *      Author: oleksandr.gonchar
 */

#ifndef DL_DLBUTTON_H_
#define DL_DLBUTTON_H_

#include <stdint.h>

typedef enum
{
  dlButtonSelect,
  dlButtonLeft,
  dlButtonRight,
  dlButtonDown,
  dlButtonUp,
  dlButtonNum
}dlButton_t;

typedef enum
{
  dlButton_Released,
  dlButton_Pressed
}dlButton_state_t;

typedef void (*ptr_event_handler)(void);

int8_t dlButton_Init (dlButton_t type, ptr_event_handler callback);

void dlButton_Run (void);

#endif /* DL_DLBUTTON_H_ */
