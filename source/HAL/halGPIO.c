/*
 * halGPIO.c
 *
 *  Created on: Feb 1, 2021
 *      Author: oleksandr.gonchar
 */

#include "halGPIO.h"
#include "stm32l4xx_hal.h"
#include "../UL/ulError.h"
#include <stdbool.h>

#pragma GCC diagnostic error "-Wswitch-enum"

#define GPIO_PIN_ALLOC_NUM  10

struct halGPIO_descr
{
  GPIO_InitTypeDef     base;
  GPIO_TypeDef *       port;
  bool                 init;
};

static halGPIO_descr_t gpio_heap[GPIO_PIN_ALLOC_NUM];

static GPIO_TypeDef * const port_table[halGPIO_Port_Num] =
{
  GPIOA,
  GPIOB,
  GPIOC,
  GPIOD,
  GPIOE
};

static const uint32_t pin_pull_table[halGPIO_Pull_Num] =
{
    GPIO_PULLUP,
    GPIO_PULLDOWN,
    GPIO_NOPULL
};

static const uint32_t pin_mode_table[halGPIO_Mode_Num] =
{
    GPIO_MODE_OUTPUT_PP,
    GPIO_MODE_INPUT,
    GPIO_MODE_AF_PP
};

static void halGPIO_Pin_Config (halGPIO_descr_t* ptr_instance, const halGPIO_Config_t config)
{
  ptr_instance->base.Pin   = (1 << config.pin);
  ptr_instance->base.Pull  = pin_pull_table[config.pull];
  ptr_instance->base.Mode  = pin_mode_table[config.mode];
  ptr_instance->base.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  ptr_instance->port       = port_table[config.port];

  HAL_GPIO_Init(port_table[config.port], &ptr_instance->base);
}

static void halGPIO_Port_Config (const halGPIO_Config_t config)
{
  switch (config.port)
  {
    case halGPIO_Port_0:
      __HAL_RCC_GPIOA_CLK_ENABLE();
      break;
    case halGPIO_Port_1:
      __HAL_RCC_GPIOB_CLK_ENABLE();
      break;
    case halGPIO_Port_2:
      __HAL_RCC_GPIOC_CLK_ENABLE();
      break;
    case halGPIO_Port_3:
      __HAL_RCC_GPIOD_CLK_ENABLE();
      break;
    case halGPIO_Port_4:
      __HAL_RCC_GPIOE_CLK_ENABLE();
      break;

    case halGPIO_Port_Num:
    default:
      break;
  }
}

halGPIO_descr_t* halGPIO_Pin_Init (const halGPIO_Config_t config)
{
  for (uint8_t i = 0; i < GPIO_PIN_ALLOC_NUM; i++)
  {
    if (!gpio_heap[i].init)
    {
      halGPIO_Port_Config(config);
      halGPIO_Pin_Config(&gpio_heap[i], config);
      gpio_heap[i].init = true;
      return &gpio_heap[i];
    }
  }
  return NULL;
}

void halGPIO_Pin_DeInit (halGPIO_descr_t* ptr_instance)
{
  ptr_instance->init = false;
}

int8_t halGPIO_Pin_Set (halGPIO_descr_t* ptr_instance)
{
  int8_t error = ulError_NULL;

  if ((ptr_instance != NULL) && (ptr_instance->init))
  {
    HAL_GPIO_WritePin(ptr_instance->port, ptr_instance->base.Pin, GPIO_PIN_SET);
    error = ulError_OK;
  }

  return error;
}

int8_t halGPIO_Pin_Reset (halGPIO_descr_t* ptr_instance)
{
  int8_t error = ulError_NULL;

  if ((ptr_instance != NULL) && (ptr_instance->init))
  {
    HAL_GPIO_WritePin(ptr_instance->port, ptr_instance->base.Pin, GPIO_PIN_RESET);
    error = ulError_OK;
  }

  return error;
}

halGPIO_Pin_State_t halGPIO_Pin_Get (halGPIO_descr_t* ptr_instance)
{
  halGPIO_Pin_State_t state = halGPIO_Pin_Unknonw;

  if ((ptr_instance != NULL) && (ptr_instance->init))
  {
    state = (HAL_GPIO_ReadPin(ptr_instance->port, ptr_instance->base.Pin) == GPIO_PIN_SET) ? halGPIO_Pin_High : halGPIO_Pin_Low;
  }

  return state;
}
