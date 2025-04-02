#pragma once

#include "common.h"
#include "sensor_reader.h"

class DiscreetSensorReader : public SensorReader {
	private:
		uint forw = 0;
	public:
		DiscreetSensorReader(uint f);

		void calculate(uint *values, uint size, int *out);
};
