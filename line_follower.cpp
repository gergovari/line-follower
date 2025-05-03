#include "line_follower.h"

LineFollower::LineFollower(SensorArray *s, SensorReader *r, SensorManager *m, MotorPair *mp, Steering *st) 
	: sensors(s), reader(r), manager(m), motors(mp), steering(st) {
	steering->stop();

	manager->setCallback(LineFollower::managerCb, this);
}

LineFollower::LineFollower(SensorArray *s, SensorReader *r, SensorManager *m, MotorPair *mp, Steering *st, CalibratedSensorArray *cs) 
	: LineFollower(s, r, m, mp, st) {
	calibratedSensors = cs;
}

void LineFollower::tick() {
	switch (state) {
		case LineFollowerStates::STANDBY:
			steering->stop();
			break;
		case LineFollowerStates::FOLLOW:
			manager->tick();
			break;
	}
}

void LineFollower::run(Sequence sequence) {
	if (sequence) {
		sequence(this);
	}
}

static void LineFollower::managerCb(uint *values, uint size, void *user) {
	int out = 0;

	auto *follower = (LineFollower*)user;
	auto *rawController = follower->rawController;
	auto *controller = follower->controller;
	auto *reader = follower->reader;
	auto *steering = follower->steering;
	
	if (!controller) {
		rawController->calculate(values, size, &out);
	} else if (reader) {
		reader->calculate(values, size, &out);
		controller->calculate(out, &out);
	}
	steering->setTarget(out);
}
