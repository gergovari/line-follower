#pragma once

#include "common.h"
#include "sensor.h"

/* Kiolvastuk a szenzor analóg értékét, 
 * de ezt fel kell dolgoznunk hogy használható legyen. */
class CalibratedSensor : public Sensor {
	private:
		Sensor *sensor;
		uint rawHighest;
		uint rawLowest;

	public:
		/* A keresett vonal általában fekete és 0-át ad a szenzorra, 
		 * de mi arra akarjuk a felső értéket ezért megfordíthatjuk. */
		bool reversed = true;

		CalibratedSensor(Sensor *s);
		CalibratedSensor(Sensor *s, bool r);

		/* A megadott szenzor kalibrált 
		 * és normalizált értékét olvassa ki. */
		uint get();
		
		/* A pillanatnyi értéket hozzáveti az eddigi min/max értékekhez,
		 * és elmenti ha alulmúlja/megugorja az eddigi értékeket. */
		void calibrate();
};

