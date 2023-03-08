/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

extern uint16_t logo[162*38];
/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
void K1PressState(uint8_t b_pressed);
float getDt();
float getOneOverDt();
void resetCounter();

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_Pin GPIO_PIN_3
#define LED_GPIO_Port GPIOE
#define K1_Pin GPIO_PIN_13
#define K1_GPIO_Port GPIOC
#define K1_EXTI_IRQn EXTI15_10_IRQn
#define CSS_Pin GPIO_PIN_1
#define CSS_GPIO_Port GPIOC
#define LCD_LED_Pin GPIO_PIN_10
#define LCD_LED_GPIO_Port GPIOE
#define LCD_CSS_Pin GPIO_PIN_11
#define LCD_CSS_GPIO_Port GPIOE
#define LCD_WR_RS_Pin GPIO_PIN_13
#define LCD_WR_RS_GPIO_Port GPIOE
#define KB_COL0_Pin GPIO_PIN_6
#define KB_COL0_GPIO_Port GPIOC
#define KB_ROW0_Pin GPIO_PIN_8
#define KB_ROW0_GPIO_Port GPIOA
#define CSSF1_Pin GPIO_PIN_6
#define CSSF1_GPIO_Port GPIOD
#define CSSF0_Pin GPIO_PIN_6
#define CSSF0_GPIO_Port GPIOB
#define SPULSE_Pin GPIO_PIN_9
#define SPULSE_GPIO_Port GPIOB
#define SPULSE_EXTI_IRQn EXTI9_5_IRQn

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
