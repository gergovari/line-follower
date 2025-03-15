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
	uint *values = malloc(size * sizeof(uint));
	
	for (int i = 0; i < size; i++) {
		values[i] = sensors[i]->get();
	}

	callback(values, size);
	free(values);
}
