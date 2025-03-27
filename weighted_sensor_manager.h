#pragma once

#include "common.h"
#include "sensor_manager.h"

typedef void(*WeightedSensorManagerCallback)(int);

class WeightedSensorManager {
	private:
		WeightedSensorManagerCallback cb;
		SensorManager *manager;

		static void callback(uint *values, uint size, void* user);
	public:
		uint target = 0;
		double *weights;

		WeightedSensorManager(SensorManager *m, uint t, double *w);
		
		void setCallback(WeightedSensorManagerCallback cb);
		void tick();
};
