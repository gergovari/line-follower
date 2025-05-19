#include "pid_controller.h"

#include <Arduino.h>

void PIDController::calculate(int in, int *out) {
	unsigned long now = millis();
	unsigned long deltaTime = (double)(now - lastTime);
	

	int target = parameters.target;
	double kp = parameters.kp;
	double ki = parameters.ki;
	double kd = parameters.kd;

	int error = parameters.target - in;
	int deltaError;

	errorSum += error * deltaTime;
	deltaError = (error - lastError) / deltaTime;

	(*out) = constrain(kp * error + ki * errorSum + kd * deltaError, 
			lowest, highest);

	lastError = error;
	lastTime = now;
}
