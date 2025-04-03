#include "calibrated_sensor.h"

#include <Arduino.h>

CalibratedSensor::CalibratedSensor(Sensor *s, bool r) {
	reversed = r;
	sensor = s;
	
	rawHighest = sensor->lowest;
	rawLowest = sensor->highest;

	lowest = 0;
	highest = 1000;
}

CalibratedSensor::CalibratedSensor(Sensor *s) : CalibratedSensor(s, true) {}

uint CalibratedSensor::get() {
	uint value = sensor->get();
	
	return (reversed) * (highest) - constrain(map(value, rawLowest, rawHighest, lowest, highest), lowest, highest);
}

void CalibratedSensor::calibrate() {
	uint value = sensor->get();

	rawHighest = value > rawHighest ? value : rawHighest;
	rawLowest = value < rawLowest ? value : rawLowest;
}
