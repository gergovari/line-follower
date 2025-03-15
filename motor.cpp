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

void Motor::setSpeed(uint s) {
	analogWrite(speed, map(constrain(s, inLowest, inHighest), inLowest, inHighest, outLowest, outHighest));
}
