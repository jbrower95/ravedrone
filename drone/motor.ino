#include "motor.h"

// global motor state
motor_t motor;
// global servo for driving motors
Servo motorServo;


/* initialize the global motor */
void setupMotor() {
  makeMotor(6, &motor, &motorServo);
}

/* Initializes a motor */
static void makeMotor(int pin, motor_t *m, Servo *motorServo) {
	pinMode(pin, OUTPUT);
	m->pin = pin;
	m->currentLevel = 0;
	m->targetLevel = 0;

        motorServo->detach();
	motorServo->attach(m->pin);

	motorServo->writeMicroseconds(MIN_MICROSECONDS);
}

// gets the microseconds mapped to by the motor
int getMotorMicroseconds(motor_t *m) {
	int us = map(m->currentLevel,
		     MIN_LEVEL, MAX_LEVEL,
		     MIN_MICROSECONDS, MAX_MICROSECONDS);
	us = constrain(us,
                       MIN_MICROSECONDS, MAX_MICROSECONDS);
	return us;
}

// takes in a motor, and will increment currentLevel to targetLevel
// this so there's a smooth ramp up to the target
// returns 1 if motor is already at target
int tickMotorLevel(motor_t *m) {
	if (m->currentLevel < m->targetLevel) {
		int nextLevel = m->currentLevel + TICK_LEVEL;
		nextLevel = constrain(nextLevel,
				      MIN_LEVEL, m->targetLevel);

		m->currentLevel = nextLevel;
		return 0;
	} else if (m->currentLevel > m->targetLevel) {
		int nextLevel = m->currentLevel - TICK_LEVEL;
		nextLevel = constrain(nextLevel,
				      m->targetLevel, MAX_LEVEL);

		m->currentLevel = nextLevel;
		return 0;
	}
	
	return 1;
}

// this will increment the motor and send the speed
void tickMotor() {
        if (tickMotorLevel(&motor)) {
            return;
        }

	motorServo.detach();
	motorServo.attach(motor.pin);

	motorServo.writeMicroseconds(
		getMotorMicroseconds(&motor));	
}

// sets the global motor's target throttle
void setMotorTarget(int target) {
   motor.targetLevel = constrain(target, MIN_LEVEL, MAX_LEVEL); 
}
