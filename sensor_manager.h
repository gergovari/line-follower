#pragma once

#include "common.h"
#include "calibrated_sensor.h"

typedef void(*SensorManagerCallback)(uint*, uint, void*);

/* Lehetővé teszi hogy egyszerűen megkapjuk a szenzorok értékeit, 
 * bármilyen frissitési megoldást is használunk. */
class SensorManager {
	private:
		SensorManagerCallback callback;
		uint size;
		CalibratedSensor **sensors;
		void *user;

	public:
		SensorManager(Sensor **se, uint si);
		
		/* Minden sikeres szenzor beolvasásnál meghívjuk az itt megadott függv. 
		 * Ezek az értékek már kalibrálva és normalizálva vannak. */
		void setCallback(SensorManagerCallback cb, void *u);
		
		/* Szenzorok szélsőértékének kalibrálása. */
		void calibrate();

		/* Szenzorok olvasásának indítása. */
		void tick();
};
