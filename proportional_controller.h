#pragma once

#include "common.h"
#include "controller.h"

class ProportionalController : public Controller {
	private:
		int target = 0;

	public:
		double kp = 1;

		ProportionalController(int t, double p);

		void calculate(int in, int *out);
};
