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
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define PWM_LED4_Pin GPIO_PIN_0
#define PWM_LED4_GPIO_Port GPIOA
#define PWM_LED3_Pin GPIO_PIN_1
#define PWM_LED3_GPIO_Port GPIOA
#define PWM_LED2_Pin GPIO_PIN_2
#define PWM_LED2_GPIO_Port GPIOA
#define PWM_LED1_Pin GPIO_PIN_3
#define PWM_LED1_GPIO_Port GPIOA
#define Press_AD1_Pin GPIO_PIN_4
#define Press_AD1_GPIO_Port GPIOA
#define Press_AD2_Pin GPIO_PIN_5
#define Press_AD2_GPIO_Port GPIOA
#define Press_AD3_Pin GPIO_PIN_6
#define Press_AD3_GPIO_Port GPIOA
#define Press_AD4_Pin GPIO_PIN_7
#define Press_AD4_GPIO_Port GPIOA
#define Press_AD5_Pin GPIO_PIN_4
#define Press_AD5_GPIO_Port GPIOC
#define Press_AD6_Pin GPIO_PIN_5
#define Press_AD6_GPIO_Port GPIOC
#define BT_RST_Pin GPIO_PIN_3
#define BT_RST_GPIO_Port GPIOB
#define PWM_LED6_Pin GPIO_PIN_7
#define PWM_LED6_GPIO_Port GPIOB
#define PWM_LED5_Pin GPIO_PIN_8
#define PWM_LED5_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void Flash_EnableReadProtection(void);

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
