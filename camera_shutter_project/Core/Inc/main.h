/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
extern ADC_HandleTypeDef hadc1;
extern ADC_HandleTypeDef hadc2;
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim17;
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define JMPR0_Pin GPIO_PIN_0
#define JMPR0_GPIO_Port GPIOA
#define LED_G_Pin GPIO_PIN_4
#define LED_G_GPIO_Port GPIOA
#define LED_R_Pin GPIO_PIN_5
#define LED_R_GPIO_Port GPIOA
#define Vbat_switched_Pin GPIO_PIN_6
#define Vbat_switched_GPIO_Port GPIOA
#define SERVO_PWM_Pin GPIO_PIN_7
#define SERVO_PWM_GPIO_Port GPIOA
#define Vusb_Pin GPIO_PIN_0
#define Vusb_GPIO_Port GPIOB
#define RCVR_Pin GPIO_PIN_15
#define RCVR_GPIO_Port GPIOA
#define RCVR_EXTI_IRQn EXTI15_10_IRQn
#define SERVO_PWR_Pin GPIO_PIN_5
#define SERVO_PWR_GPIO_Port GPIOB
#define BTN0_Pin GPIO_PIN_8
#define BTN0_GPIO_Port GPIOB
#define BTN0_EXTI_IRQn EXTI9_5_IRQn
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
