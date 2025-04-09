#pragma once

#include "common.h"

class Controller {
	public:
		int highest = 1000;
		int lowest = -1000;

		virtual void calculate(int in, int *out) = 0;
};
