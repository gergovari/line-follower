#pragma once

#include "common.h"
#include "sensor.h"

typedef void(*SensorManagerCallback)(uint*, uint) ;

class SensorManager {
	private:
		SensorManagerCallback callback;
		uint size;
		Sensor **sensors;

	public:
		SensorManager(Sensor **se, uint si);
		
		/* Minden sikeres szenzor beolvasásnál meghívjuk az itt megadott függv. 
		 * Ezek az értékek már kalibrálva és normalizálva vannak. */
		void setCallback(SensorManagerCallback cb);
		
		/* Szenzorok olvasásának indítása. */
		void tick();
};
