#include "discreet_sensor_reader.h"

#include <Arduino.h>

DiscreetSensorReader::DiscreetSensorReader(uint c) {
	cutoff = c;
}

void DiscreetSensorReader::calculate(uint *values, uint size, int *out) {
	if (size % 2 != 0) return;
	int temp = 0;

	for (uint i = 0; i < size / 2; i++) {
		temp += values[i] * ((double)1 / pow(2, i));
		if (temp < cutoff) {
			temp = 0;
		}
	}
	(*out) -= constrain(temp, 0, max(abs(lowest), abs(highest)));
	
	temp = 0;
	for (uint i = size / 2; i < size; i++) {
		temp += values[i] * ((double)1 / pow(2, (size - 1) - i));
		if (temp < cutoff) {
			temp = 0;
		}
	}
	(*out) += constrain(temp, 0, max(abs(lowest), abs(highest)));
}
