#include "steering.h"

#include <Arduino.h>

void Steering::setTarget(signed int t) {
	signed int l = 0;
	signed int r = 0;

	t = constrain(t, lowest, highest);
	
	l = left->highest + t;
	r = right->highest - t;

	left->setSpeed(l);
	right->setSpeed(r);
}

void Steering::stop() {
	left->setSpeed(0);
	right->setSpeed(0);
}
