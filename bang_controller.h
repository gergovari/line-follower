#pragma once

#include "common.h"
#include "controller.h"

class BangController : public Controller {
	public:
		void calculate(int in, int *out);
};
