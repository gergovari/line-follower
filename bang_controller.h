#pragma once

#include "common.h"
#include "controller.h"

class BangController : public Controller {
	private:
		bool useFull = false;

	public:
		BangController(bool u);

		void calculate(int in, int *out);
};

