#pragma once

#include "common.h"
#include "sensor_reader.h"

class SensorReader {
	public:
		static const int lowest = -1000;
		static const int highest = 1000;

		static void calculate(uint *values, uint size, int *out);
};
