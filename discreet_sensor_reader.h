#pragma once

#include "common.h"
#include "sensor_reader.h"

class DiscreetSensorReader : public SensorReader {
	private:
		uint cutoff = 0;
	public:
		DiscreetSensorReader(uint c);

		void calculate(uint *values, uint size, int *out);
};
