/*
 * halGPIO.h
 *
 *  Created on: Feb 1, 2021
 *      Author: oleksandr.gonchar
 */

#ifndef HAL_HALGPIO_H_
#define HAL_HALGPIO_H_

#include <stdint.h>

typedef struct halGPIO_descr halGPIO_descr_t;

typedef enum
{
  halGPIO_Port_0,
  halGPIO_Port_1,
  halGPIO_Port_2,
  halGPIO_Port_3,
  halGPIO_Port_4,
  halGPIO_Port_Num
}halGPIO_Port_t;

typedef enum
{
  halGPIO_Pin_0,
  halGPIO_Pin_1,
  halGPIO_Pin_2,
  halGPIO_Pin_3,
  halGPIO_Pin_4,
  halGPIO_Pin_5,
  halGPIO_Pin_6,
  halGPIO_Pin_7,
  halGPIO_Pin_8,
  halGPIO_Pin_Num
}halGPIO_Pin_t;

typedef enum
{
  halGPIO_Mode_Out,
  halGPIO_Mode_In,
  halGPIO_Mode_Alt,
  halGPIO_Mode_Num
}halGPIO_Mode_t;

typedef enum
{
  halGPIO_Pin_High,
  halGPIO_Pin_Low,
  halGPIO_Pin_Unknonw
}halGPIO_Pin_State_t;

typedef enum
{
  halGPIO_Pull_Up,
  halGPIO_Pull_Down,
  halGPIO_Pull_NoPull,
  halGPIO_Pull_Num,
}halGPIO_Pin_Pull_t;

typedef struct
{
  halGPIO_Port_t      port;
  halGPIO_Pin_t       pin;
  halGPIO_Mode_t      mode;
  halGPIO_Pin_Pull_t  pull;
  halGPIO_Pin_State_t state;
}halGPIO_Config_t;

halGPIO_descr_t* halGPIO_Pin_Init (const halGPIO_Config_t config);
void halGPIO_Pin_DeInit (halGPIO_descr_t* ptr_instance);

int8_t halGPIO_Pin_Set (halGPIO_descr_t* ptr_instance);
int8_t halGPIO_Pin_Reset (halGPIO_descr_t* ptr_instance);

halGPIO_Pin_State_t halGPIO_Pin_Get (halGPIO_descr_t* ptr_instance);

#endif /* HAL_HALGPIO_H_ */
