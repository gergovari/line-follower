#include "discreet_sensor.h"

#include <Arduino.h>

DiscreetSensor::DiscreetSensor(Sensor *s, double t) {
	sensor = s;
	threshold = t;
}

uint DiscreetSensor::get() {
	return sensor->get() > sensor->highest * threshold ? highest : lowest;
}
