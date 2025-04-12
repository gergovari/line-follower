#pragma once

#include "common.h"
#include "controller.h"

class ProportionalController : public Controller {
	public:
		int target = 0;
		double kp = 1;

		ProportionalController(int t, double p);

		void calculate(int in, int *out);
};
