#pragma once

#include "common.h"
#include "controller.h"

class IntegralController : public Controller {
	private:
		long previous = 0;
		long long cumulative = 0;

	public:
		double ki = 1;

		IntegralController(double i);

		void calculate(int in, int *out);
};
