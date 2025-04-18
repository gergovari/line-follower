#include "integral_controller.h"

#include <Arduino.h>

IntegralController::IntegralController(double i) {
	ki = i;
}

void IntegralController::calculate(int in, int *out) {
	long current = millis();
	long elapsed = current - previous;

	previous = current;

	cumulative = cumulative + in * elapsed;
	(*out) = constrain(ki * cumulative, lowest, highest);
}
