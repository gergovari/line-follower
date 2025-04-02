#pragma once

#include "common.h"

class RawController {
	public:
		virtual void calculate(int* values, uint size, int *out);
};
