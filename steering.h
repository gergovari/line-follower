#pragma once

#include "common.h"
#include "motor.h"

/* Absztrakció a kormányzásra, a motorokat kezeli hogy az adott irányba menjünk. */
class Steering {
	private:
		Motor *left;
		Motor *right;
	
	public:
		signed int lowest = -1000;
		signed int highest = 1000;

		Steering(Motor *l, Motor *r);

		void setTarget(signed int t);
		void stop();
};
