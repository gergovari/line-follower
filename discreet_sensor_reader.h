#pragma once

#include "common.h"
#include "sensor_reader.h"
#include "symmetric_sensor_reader.h"

class DiscreetSensorReader : public SensorReader {
	private:
		uint cutoff = 0;
		SymmetricSensorReader *reader;

	public:
		DiscreetSensorReader(uint c);
		~DiscreetSensorReader();

		void calculate(uint *values, uint size, int *out);
};
