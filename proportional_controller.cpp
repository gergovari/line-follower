#include "proportional_controller.h"

#include <Arduino.h>

ProportionalController::ProportionalController(int t, double p) {
	target = t;
	kp = p;
}

void ProportionalController::calculate(int in, int *out) {
	(*out) = constrain(kp * -(target - in), lowest, highest);
}
