/*
 * shutter_control.c
 *
 *  Created on: Nov 26, 2021
 *      Author: Fongberg
 */

#include "servo.h"
#include "shutter_control.h"
#include "stm32g4xx_hal.h"

#define SERVO_TRANSIT_DELAY 1000

void ShutterControlTriggerShutter() {
  ServoSetPosition(100);
  ServoEnablePower();
  HAL_Delay(SERVO_TRANSIT_DELAY);
  ServoSetPosition(0);
  HAL_Delay(SERVO_TRANSIT_DELAY);
  ServoDisablePower();
}
