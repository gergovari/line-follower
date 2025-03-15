#pragma once

#include "common.h"
#include "sensor.h"

class RawSensor : public Sensor {
	private:
		Pin pin;
	public:
		RawSensor(Pin p);

		/* A megadott szenzor nyers értékét olvassa ki. */
		uint get();
};
