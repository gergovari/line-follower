#include "calibrated_sensor_array.h"

#include <stddef.h>

void CalibratedSensorArray::calibrate() {
	for (size_t i = 0; i < size; i++) {
		sensors[i].calibrate();
	}
}
