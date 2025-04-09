#pragma once

#include "common.h"

class Sensor {
	public:
		uint lowest;
		uint highest;

		virtual uint get() = 0;
};
