#include "calibrated_sensor.h"

#include <Arduino.h>

CalibratedSensor::CalibratedSensor(Sensor *s, bool r) {
	reversed = r;
	sensor = s;
	
	/* Megfordítjuk a szélsőértékeket hogy legyen mihez majd kalibrálni. */
	rawHighest = sensor->lowest;
	rawLowest = sensor->highest;

	lowest = 0;
	highest = 1000;
}

CalibratedSensor::CalibratedSensor(Sensor *s) : CalibratedSensor(s, true) {}

uint CalibratedSensor::get() {
	uint value = sensor->get();
	
	/* Remap-eljük a nyers értéket a kalibráció alapján 
	 * és normalizáljuk 0-1000 értékre. */
	return (reversed) * (highest) - constrain(map(value, rawLowest, rawHighest, lowest, highest), lowest, highest);
}

/* Megnézi hogy az éppeni érték szélsőérték -e. */
void CalibratedSensor::calibrate() {
	uint value = sensor->get();

	rawHighest = value > rawHighest ? value : rawHighest;
	rawLowest = value < rawLowest ? value : rawLowest;
}
