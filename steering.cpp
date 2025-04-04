#include "steering.h"

#include <Arduino.h>

Steering::Steering(Motor *l, Motor *r) {
	left = l;
	right = r;
}

void Steering::setTarget(signed int t) {
	signed int l = 0;
	signed int r = 0;

	t = constrain(t, lowest, highest);
	
	if (t > 0) {
		l = (signed int)(left->highest * ((float)t / highest));
		r = 0;
	} else if (t < 0) {
		t = abs(t);
		l = 0;
		r = (signed int)(right->highest * ((float)t / highest));
	} else {
		l = left->highest;
		r = right->highest;
	}

	left->setSpeed(l);
	right->setSpeed(r);
}

void Steering::stop() {
	left->setSpeed(0);
	right->setSpeed(0);
}
