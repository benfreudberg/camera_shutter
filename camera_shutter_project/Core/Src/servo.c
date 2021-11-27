/*
 * servo.c
 *
 *  Created on: Nov 26, 2021
 *      Author: Fongberg
 */

#include "main.h"

#define SERVO_MIN_US    500
#define SERVO_RANGE_US  1500

void ServoEnablePower() {
  HAL_GPIO_WritePin(SERVO_PWR_GPIO_Port, SERVO_PWR_Pin, GPIO_PIN_SET);
}

void ServoDisablePower() {
  HAL_GPIO_WritePin(SERVO_PWR_GPIO_Port, SERVO_PWR_Pin, GPIO_PIN_RESET);
}

void ServoSetPosition(float position) {
  htim17.Instance->CCR1 = SERVO_MIN_US + (uint32_t)(position*SERVO_RANGE_US/100);
}

void ServoInit() {
  HAL_TIM_PWM_Start(&htim17, TIM_CHANNEL_1);
  ServoSetPosition(0);
  ServoEnablePower();
  HAL_Delay(1000);
  ServoDisablePower();
}
