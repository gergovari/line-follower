#pragma once

#include "common.h"
#include "sensor.h"

class DiscreetSensor : public Sensor {
	private:
		Sensor *sensor;
		double threshold;
		
		uint highest = 1000;
		uint lowest = 0;

	public:
		DiscreetSensor(Sensor *s, double t);

		uint get();
};

