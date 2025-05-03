#include "memory_sensor_reader.h"

#include <Arduino.h>

void MemorySensorReader::calculate(uint *values, uint size, int *out) {
	uint cutoff = reader->cutoff;

	reader->calculate(values, size, out);

	if ((values[1] > cutoff || values[2] > cutoff) 
			&& (values[0] < cutoff && values[3] < cutoff)) {
		*out = 0;
	} else if (*out == 0) {
		*out = last;
	}
	
	last = *out != 0 ? *out : last;
}
