#pragma once

#include "sensor_array.h"
#include "calibrated_sensor.h"

class CalibratedSensorArray : public SensorArray {
	public:
		bool calibrated = true;
		CalibratedSensor *sensors;

		CalibratedSensorArray(Sensor *s, size_t si) : SensorArray(s, si) {};

		void calibrate();
};
