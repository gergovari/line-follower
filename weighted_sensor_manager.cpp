#include "weighted_sensor_manager.h"

#include <Arduino.h>

WeightedSensorManager::WeightedSensorManager(SensorManager *m, uint t, double *w) {
	manager = m;
	target = t;
	weights = w;

	manager->setCallback(callback, this);
}

static void WeightedSensorManager::callback(uint *values, uint size, void* user) {
	auto instance = (WeightedSensorManager*)user;
	int result = 0;

	for (uint i = 0; i < size; i++) {
		result += instance->weights[i] * ((int)values[i] - (int)values[instance->target]);
	}
	instance->cb(result);
}

void WeightedSensorManager::setCallback(WeightedSensorManagerCallback c) {
	cb = c;
}


void WeightedSensorManager::tick() {
	manager->tick();
}
