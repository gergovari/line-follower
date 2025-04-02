#pragma once

#include "common.h"
#include "raw_controller.h"

class BangRawController : public RawController {
	private:
		bool useFull = false;
	public:
		BangRawController(bool u);
		void calculate(int* values, uint size, int *out);
};

