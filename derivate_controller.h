#pragma once

#include "common.h"
#include "controller.h"

class DerivateController : public Controller {
	private:
		long previous = 0;
		int last = 0;

	public:
		double kd = 1;

		DerivateController(double d);

		void calculate(int in, int *out);
};
