#include "pid3_controller.h"

#include <Arduino.h>

void PID3Controller::calculate(int in, int *out) {
	input = in;
	controller.Compute();
	(*out) = output;
}

void PID3Controller::reconfigure() {
	controller = PID(&input, &output, &parameters.target, 
			parameters.kp, parameters.ki, parameters.kd, 
			DIRECT);
}
