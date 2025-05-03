#pragma once

#include "common.h"
#include "discreet_sensor_reader.h"

class MemorySensorReader : public SensorReader {
	private:
		int last;
		DiscreetSensorReader *reader;

	public:
		MemorySensorReader(SensorReader *r) : reader(r) {};

		void calculate(uint *values, uint size, int *out);
};
