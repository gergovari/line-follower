#include "motor.h"

#include <Arduino.h>

Motor::Motor(Pin f, Pin b, Pin s) {
	forward = f;
	backward = b;
	speed = s;

	pinMode(forward, OUTPUT);
	pinMode(backward, OUTPUT);
	pinMode(speed, OUTPUT);
	
	setSpeed(0);
}

void Motor::setDirection(Direction dir) {
	bool f = false;
	bool b = false;

	switch (dir) {
		case Direction::FORWARD:
			f = true;
			b = false;
			break;
		case Direction::BACKWARD:
			f = false;
			b = true;
			break;
		case Direction::BRAKE:
		default:
			f = true;
			b = true;
	}

	digitalWrite(forward, f);
	digitalWrite(backward, b);
}

void Motor::setSpeed(signed int s) {
	s = constrain(s, lowest, highest);
	
	if (s == 0) {
		setDirection(Direction::BRAKE);
		analogWrite(speed, 0);
	} else {
		setDirection(s > 0 ? Direction::FORWARD : Direction::BACKWARD);
		analogWrite(speed, map(abs(s), 0, highest, outLowest, outHighest));
	}
}
