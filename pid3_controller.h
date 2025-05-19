#pragma once

#include "common.h"
#include "controller.h"

#include <PID_v1.h>

struct PID3Parameters {
	double target = 0;

	double kp = 0;
	double ki = 0;
	double kd = 0;

	PID3Parameters(double t = 0, double p = 0, double i = 0, double d = 0)
		: target(t), kp(p), ki(i), kd(d) {}
};

class PID3Controller : public Controller {
	private:
		double input, output;
		PID controller;

	public:
		PID3Parameters parameters;

		PID3Controller::PID3Controller(PID3Parameters pa) : parameters(pa),
			controller(&input, &output, &parameters.target, 
					parameters.kp, parameters.ki, parameters.kd, DIRECT) {
				controller.SetMode(AUTOMATIC);
			};

		void calculate(int in, int *out);
};
