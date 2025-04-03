#pragma once

#include "common.h"
#include "calibrated_sensor.h"

typedef void(*SensorManagerCallback)(uint*, uint, void*);

class SensorManager {
	private:
		SensorManagerCallback callback;
		uint size;
		Sensor **sensors;
		void *user;

	public:
		SensorManager(Sensor **se, uint si);
		
		void setCallback(SensorManagerCallback cb, void *u);
		void tick();
};
