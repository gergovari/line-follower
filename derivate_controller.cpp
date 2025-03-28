#include "derivate_controller.h"

#include <Arduino.h>

DerivateController::DerivateController(double d) {
	kd = d;
}

void DerivateController::calculate(int in, int *out) {
	long current = millis();
	long elapsed = current - previous;

	previous = current;
	
	int rate = (in - last) / elapsed;
	last = in;
	(*out) = kd * rate;
}
