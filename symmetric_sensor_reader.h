#pragma once

#include "common.h"
#include "sensor_reader.h"

class SymmetricSensorReader : public SensorReader {
	public:
		static void calculate(uint *values, uint size, int *out);
};
