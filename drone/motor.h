#ifndef MOTOR_H
#define MOTOR_H

#include "Arduino.h"
#include <Servo.h>

// TODO: expose constants / functions.
const int MIN_MICROSECONDS = 600;
const int MAX_MICROSECONDS = 1100;

const int MIN_LEVEL = 0;
const int MAX_LEVEL = 2000;

const unsigned int TICK_LEVEL = 10;

struct motor_t {
	int pin;

	int currentLevel;
	int targetLevel;
};

void setupMotor();
void makeMotor(int pin, motor_t &m, Servo motorServo);
int getMotorMicroseconds(motor_t &m);
int tickMotorLevel(motor_t &m);
void tickMotor();
void setMotorTarget(int target);

#endif
