#pragma once

#include "common.h"
#include "controller.h"

#include "proportional_controller.h"
#include "integral_controller.h"
#include "derivate_controller.h"

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
		long previous = 0;
		int last = 0;
	public:
		ProportionalController *p;
		IntegralController *i;
		DerivateController *d;

		PIDParameters parameters;

		PIDController(PIDParameters pa);
		~PIDController();

		void calculate(int in, int *out);
};
