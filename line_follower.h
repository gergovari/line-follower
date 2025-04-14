#pragma once

#include "raw_controller.h"
#include "controller.h"

#include "sensor_array.h"
#include "sensor_reader.h"
#include "sensor_manager.h"

#include "motor_pair.h"
#include "steering.h"

class LineFollower;

typedef void *(Sequence)(LineFollower*);

enum class LineFollowerStates {
	STANDBY,
	FOLLOW,
};

class LineFollower {
	private:
		LineFollower(SensorArray *s, SensorReader *r, SensorManager *m, MotorPair *mp, Steering *st);
	public:
		RawController *rawController = nullptr;
		Controller *controller = nullptr;

		SensorArray *sensors;
		SensorReader *reader;
		SensorManager *manager;
		
		MotorPair *motors;
		Steering *steering;

		LineFollowerStates state;
		
		LineFollower(RawController *c, 
			SensorArray *s, 
			SensorReader *r, 
			SensorManager *m, 
			MotorPair *mp, 
			Steering *st) : LineFollower(s, r, m, mp, st) {
			/* Dumb limitation requires this workaround...
			 * Probably there's a reason but I don't get it. */
			rawController = c;
		};
		LineFollower(Controller *c, 
			SensorArray *s, 
			SensorReader *r, 
			SensorManager *m, 
			MotorPair *mp, 
			Steering *st) : LineFollower(s, r, m, mp, st) {
			controller = c;
		};

		static void managerCb(uint *values, uint size, void *user);

		void tick();
		void run(Sequence sequence);
};
