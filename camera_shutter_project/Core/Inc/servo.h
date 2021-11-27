/*
 * servo.h
 *
 *  Created on: Nov 26, 2021
 *      Author: Fongberg
 */

#ifndef INC_SERVO_H_
#define INC_SERVO_H_

void ServoEnablePower();
void ServoDisablePower();
//value from 0% to 100%
void ServoSetPosition(float position);
void ServoInit();

#endif /* INC_SERVO_H_ */
