#pragma once

#include <stddef.h>

#include "calibrated_sensor.h"

class CalibratedSensorArray {
	public:
		bool calibrated = true;
		size_t size;

		CalibratedSensor **sensors;

		CalibratedSensorArray(CalibratedSensor **s, size_t si) : sensors(s), size(si) {};

		void calibrate();
};
