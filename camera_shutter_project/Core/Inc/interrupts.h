/*
 * interrupts.h
 *
 *  Created on: Nov 26, 2021
 *      Author: Fongberg
 */

#ifndef INC_INTERRUPTS_H_
#define INC_INTERRUPTS_H_

typedef enum _InterruptSource {
  INTERRUPT_SOURCE_TARGET_CODE_RECEIVED,
  INTERRUPT_SOURCE_BUTTON_PRESSED,
  INTERRUPT_SOURCE_NUM_SOURCES,
} InterruptSource;

void SetInterruptCallback(InterruptSource source, void(*callback)(void));

#endif /* INC_INTERRUPTS_H_ */
