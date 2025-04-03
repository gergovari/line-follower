#pragma once

#include "common.h"
#include "sensor.h"

class RawSensor : public Sensor {
	private:
		Pin pin;
	public:
		RawSensor(Pin p);

		uint get();
};
