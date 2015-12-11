#ifndef MOTOR_H
#define MOTOR_H

#include "Arduino.h"
#include <Servo.h>

// ranges of microsecond servo signal to send to ESC
const int MIN_MICROSECONDS = 600;
const int MAX_MICROSECONDS = 1100;

// ranges of throttle level used in code
const int MIN_LEVEL = 0;
const int MAX_LEVEL = 2000;

// amount to change in levels
const unsigned int TICK_LEVEL = 10;

// holds a motor state
struct motor_t {
	int pin;

	int currentLevel;
	int targetLevel;
};

// call to initialize the default motor globals
void setupMotor();

// constructs a motor that outputs to pin, stores state in m
void makeMotor(int pin, motor_t *m, Servo motorServo);

// gets the microseconds signal that the current motor's throttle is at
int getMotorMicroseconds(motor_t *m);

// increments/decrements the motor throttle to get to target throttle
int tickMotorLevel(motor_t *m);

// ticks the global motor, for smooth throttling
void tickMotor();

// sets the target throttle to ramp up towards
void setMotorTarget(int target);

#endif
