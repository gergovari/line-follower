#pragma once

#include "common.h"
#include "sensor.h"

class CalibratedSensor : public Sensor {
	private:
		Sensor *sensor;
		uint rawHighest;
		uint rawLowest;

	public:
		CalibratedSensor(Sensor *s);

		/* A megadott szenzor kalibrált 
		 * és normalizált értékét olvassa ki. */
		uint get();
		
		/* A pillanatnyi értéket hozzáveti az eddigi min/max értékekhez,
		 * és elmenti ha alulmúlja/megugorja az eddigi értékeket. */
		void calibrate(uint *l, uint *h);
};

