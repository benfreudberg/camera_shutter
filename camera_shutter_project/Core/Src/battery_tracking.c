/*
 * battery_tracking.c
 *
 *  Created on: Nov 26, 2021
 *      Author: Fongberg
 */

#include "battery_tracking.h"
#include "main.h"
#include <stdio.h>

typedef enum _UsbState {
  USB_STATE_NOT_POWERED,
  USB_STATE_POWERED
} UsbState;

typedef enum _BatteryState {
  BATTERY_STATE_LOW,
  BATTERY_STATE_MED,
  BATTERY_STATE_FULL
} BatteryState;

#define BATTERY_VOLTAGE_LOW_UPPER_LIMIT 1650
#define BATTERY_VOLTAGE_MED_UPPER_LIMIT 2000
#define USB_VOLTAGE_NOT_POWERED_UPPER_LIMIT 1800

static inline UsbState GetUsbState() {
  HAL_ADC_Start(&hadc1);
  HAL_ADC_PollForConversion(&hadc1, 100);
  uint32_t usb_raw_voltage = HAL_ADC_GetValue(&hadc1);
  printf("usb_raw_voltage is %lu\n", usb_raw_voltage);
  HAL_Delay(10);
  HAL_ADC_Stop(&hadc1);
  if (usb_raw_voltage < USB_VOLTAGE_NOT_POWERED_UPPER_LIMIT) {
    return USB_STATE_NOT_POWERED;
  } else {
    return USB_STATE_POWERED;
  }
}

static inline BatteryState GetBatteryState() {
  HAL_ADC_Start(&hadc2);
  HAL_ADC_PollForConversion(&hadc2, 100);
  uint32_t battery_raw_voltage = HAL_ADC_GetValue(&hadc2);
  printf("battery_raw_voltage is %lu\n", battery_raw_voltage);
  HAL_Delay(10);
  HAL_ADC_Stop(&hadc2);
  if (battery_raw_voltage < BATTERY_VOLTAGE_LOW_UPPER_LIMIT) {
    return BATTERY_STATE_LOW;
  } else if (battery_raw_voltage < BATTERY_VOLTAGE_MED_UPPER_LIMIT) {
    return BATTERY_STATE_MED;
  } else {
    return BATTERY_STATE_FULL;
  }
}

void BatteryTrackingInit() {
  HAL_ADCEx_Calibration_Start(&hadc1, ADC_SINGLE_ENDED);
  HAL_ADCEx_Calibration_Start(&hadc2, ADC_SINGLE_ENDED);
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
}

void BatteryTrackingUpdate() {
  UsbState usb_state = GetUsbState();
  BatteryState battery_state = GetBatteryState();
  if (usb_state == USB_STATE_NOT_POWERED) {
    if (battery_state == BATTERY_STATE_LOW) {
      htim2.Instance->CCR1 = 9999;
    } else {
      htim2.Instance->CCR1 = 0;
    }
  } else {
    if (battery_state == BATTERY_STATE_FULL) {
      htim2.Instance->CCR1 = 0;
    } else {
      htim2.Instance->CCR1 = 4999;
    }
  }
}
