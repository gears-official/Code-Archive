#ifndef _SERVOCONTROL_H_
#define _SERVOCONTROL_H_

#include <Servo.h>

#define F_SERVO 40
#define B_SERVO 44

extern Servo frontServo;
extern Servo backServo;

void frontServoMove(int start, int end);
void backServoMove(int start, int end);

#endif // _SERVOCONTROL_H_