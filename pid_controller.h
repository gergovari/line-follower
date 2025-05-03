#pragma once

#include "common.h"
#include "controller.h"


struct PIDParameters {
	int target = 0;

	double kp = 0;
	double ki = 0;
	double kd = 0;

	PIDParameters(int t = 0, double p = 0, double i = 0, double d = 0)
		: target(t), kp(p), ki(i), kd(d) {}
};

class PIDController : public Controller {
	private:
		unsigned long lastTime;

		long errorSum;
		int lastError;

	public:
		PIDParameters parameters;

		PIDController::PIDController(PIDParameters pa) : parameters(pa) {};

		void calculate(int in, int *out);
};
