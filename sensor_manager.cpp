#include "sensor_manager.h"

#include <Arduino.h>

SensorManager::SensorManager(Sensor **se, uint si) {
	sensors = se;
	size = si;
}

void SensorManager::setCallback(SensorManagerCallback cb, void* u) {
	callback = cb;
	user = u;
}

void SensorManager::calibrate() {
	for (int i = 0; i < size; i++) {
		sensors[i]->calibrate();
	}
}

void SensorManager::tick() {
	/* malloc beágyazott rendszerben?
	 * Lehet csak odakell figyelni. Ha elég szenzort dobunk be unsafe. */
	uint *values = malloc(size * sizeof(uint));
	
	for (int i = 0; i < size; i++) {
		values[i] = sensors[i]->get();
	}

	callback(values, size, user);

	/* Aki malloc-ot mond... */
	free(values);
}
