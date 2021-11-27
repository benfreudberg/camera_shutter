/*
 * program_logic.c
 *
 *  Created on: Nov 6, 2021
 *      Author: Fongberg
 */
#include "main.h"
#include <stdio.h>
#include "stm32g431xx.h"
#include "interrupts.h"
#include "servo.h"
#include "shutter_control.h"
#include "battery_tracking.h"

#define SHUTTER_REMOTE_DELAY 3 //seconds

static inline void GreenLedOn() {
  HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, GPIO_PIN_SET);
}

static inline void GreenLedOff() {
  HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, GPIO_PIN_RESET);
}

static void Countdown(uint8_t seconds) {
  for (; seconds > 0; seconds--) {
    GreenLedOff();
    HAL_Delay(500);
    GreenLedOn();
    HAL_Delay(500);
  }
}

void TargetCodeReceivedCallback() {
  printf("TARGET_CODE received\n");
  Countdown(SHUTTER_REMOTE_DELAY);
  GreenLedOff();
  ShutterControlTriggerShutter();
  GreenLedOn();
}

void ButtonPressedCallback() {
  printf("button pressed\n");
  GreenLedOff();
  ShutterControlTriggerShutter();
  GreenLedOn();
}

void ProgramLogicInit() {
  //Set interrupt callback functions
  SetInterruptCallback(INTERRUPT_SOURCE_TARGET_CODE_RECEIVED, TargetCodeReceivedCallback);
  SetInterruptCallback(INTERRUPT_SOURCE_BUTTON_PRESSED, ButtonPressedCallback);

  //Turn on status LED (green)
  GreenLedOn();

  //initialize battery state tracking
  BatteryTrackingInit();

  //enable interrupts for RCVR timer
  __HAL_TIM_CLEAR_IT(&htim1, TIM_IT_UPDATE);
  __HAL_TIM_CLEAR_IT(&htim1, TIM_IT_CC1);
  __HAL_TIM_ENABLE_IT(&htim1, TIM_IT_UPDATE);
  __HAL_TIM_ENABLE_IT(&htim1, TIM_IT_CC1);

  //start servo
  ServoInit();
}
