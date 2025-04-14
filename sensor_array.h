#pragma once

#include "sensor.h"

#include <stddef.h>

class SensorArray {
	public:
		Sensor *sensors;
		size_t size;

		// Sorry, no RTTI on Arduino...
		bool calibrated = false;

		SensorArray(Sensor *s, size_t si) : sensors(s), size(si) {};
};
