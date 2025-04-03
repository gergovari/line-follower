#pragma once

#include "common.h"
#include "sensor.h"

class CalibratedSensor : public Sensor {
	private:
		Sensor *sensor;
		uint rawHighest;
		uint rawLowest;

	public:
		bool reversed = true;

		CalibratedSensor(Sensor *s);
		CalibratedSensor(Sensor *s, bool r);

		uint get();
		void calibrate();
};

