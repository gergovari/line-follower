#pragma once

#include "common.h"
#include "sensor_reader.h"
#include "symmetric_sensor_reader.h"

class DiscreetSensorReader : public SensorReader {
	private:
		SymmetricSensorReader *reader;

	public:
		uint cutoff = 0;

		DiscreetSensorReader(uint c);
		~DiscreetSensorReader();

		void calculate(uint *values, uint size, int *out);
};
