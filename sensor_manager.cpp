#include "sensor_manager.h"

#include <Arduino.h>

SensorManager::SensorManager(Sensor **se, uint si) {
	sensors = se;
	size = si;
}

void SensorManager::setCallback(SensorManagerCallback cb) {
	callback = cb;
}

void SensorManager::tick() {
	/* malloc beágyazott rendszerben?
	 * Lehet csak odakell figyelni. Ha elég szenzort dobunk be unsafe. */
	uint *values = malloc(size * sizeof(uint));
	
	for (int i = 0; i < size; i++) {
		values[i] = sensors[i]->get();
	}

	callback(values, size);

	/* Aki malloc-ot mond... */
	free(values);
}
