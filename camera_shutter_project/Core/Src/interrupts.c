/*
 * interrupts.c
 *
 *  Created on: Nov 26, 2021
 *      Author: Fongberg
 */


#include "main.h"
#include <stdio.h>
#include "stm32g431xx.h"
#include "interrupts.h"

const uint64_t TARGET_CODE = 0x3ffffffd77ffffff;
static uint64_t received_code = 0;
static int pulse_count = 63;
static void(*CallbackFunctions[INTERRUPT_SOURCE_NUM_SOURCES])(void) = {NULL};

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
  if (GPIO_Pin == RCVR_Pin) {
    HAL_TIM_Base_Start(&htim1);
    HAL_NVIC_DisableIRQ(EXTI15_10_IRQn);
  } else if (GPIO_Pin == BTN0_Pin) {
    HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);
    CallbackFunctions[INTERRUPT_SOURCE_BUTTON_PRESSED]();
    HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
  }
}

void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim) {
  received_code |= (uint64_t)HAL_GPIO_ReadPin(RCVR_GPIO_Port, RCVR_Pin) << pulse_count--;
  //HAL_GPIO_TogglePin(PWM_GPIO_Port, PWM_Pin);
}

void SetInterruptCallback(InterruptSource source, void(*callback)(void)) {
  CallbackFunctions[source] = callback;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
  if (htim == &htim1) {
    HAL_TIM_Base_Stop(&htim1);
    if (received_code == TARGET_CODE) {
      CallbackFunctions[INTERRUPT_SOURCE_TARGET_CODE_RECEIVED]();
    } else {
      printf("incorrect code received: 0x%08lx_%08lx\n", (uint32_t)(received_code>>32), (uint32_t)received_code);
    }
    received_code = 0;
    pulse_count = 63;
    __HAL_GPIO_EXTI_CLEAR_IT(RCVR_Pin);
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
  }
}
