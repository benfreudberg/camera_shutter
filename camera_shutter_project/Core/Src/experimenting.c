/*
 * experimenting.c
 *
 *  Created on: Nov 6, 2021
 *      Author: Fongberg
 */
#include "main.h"
#include <stdio.h>
#include "stm32g431xx.h"

const uint64_t TARGET_CODE = 0x3ffffffd77ffffff;
static uint64_t received_code = 0;
static int pulse_count = 63;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
  if (GPIO_Pin == RCVR_Pin) {
    HAL_TIM_Base_Start(&htim1);
    HAL_NVIC_DisableIRQ(EXTI15_10_IRQn);

//    HAL_Delay(900);
//    printf("interrupt on RCVR pin\n");
//    HAL_Delay(100);

//    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_Pin);
  }
}

void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim) {
  received_code |= (uint64_t)HAL_GPIO_ReadPin(RCVR_GPIO_Port, RCVR_Pin) << pulse_count--;
  HAL_GPIO_TogglePin(PWM_GPIO_Port, PWM_Pin);
}

void TargetCodeReceivedCallback() {
  printf("TARGET_CODE received!\n");
  HAL_Delay(1000);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
  if (htim == &htim1) {
    HAL_TIM_Base_Stop(&htim1);
    if (received_code == TARGET_CODE) {
      TargetCodeReceivedCallback();
    } else {
      printf("incorrect code received: 0x%08lx_%08lx\n", (uint32_t)(received_code>>32), (uint32_t)received_code);
    }
    received_code = 0;
    pulse_count = 63;
    __HAL_GPIO_EXTI_CLEAR_IT(RCVR_Pin);
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
  }
}

void CustomInit() {
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);


  __HAL_TIM_CLEAR_IT(&htim1, TIM_IT_UPDATE);
  __HAL_TIM_CLEAR_IT(&htim1, TIM_IT_CC1);
  __HAL_TIM_ENABLE_IT(&htim1, TIM_IT_UPDATE);
  __HAL_TIM_ENABLE_IT(&htim1, TIM_IT_CC1);
}
