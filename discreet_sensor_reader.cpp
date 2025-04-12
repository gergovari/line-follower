#include "discreet_sensor_reader.h"

#include <Arduino.h>

DiscreetSensorReader::DiscreetSensorReader(uint c) {
	cutoff = c;
	reader = new SymmetricSensorReader();
}

DiscreetSensorReader::~DiscreetSensorReader() {
	delete reader;
}

void DiscreetSensorReader::calculate(uint *values, uint size, int *out) {
	reader->calculate(values, size, out);
	
	(*out) = abs(*out) < cutoff ? 0 : (*out);
	Serial.println(*out);
}
