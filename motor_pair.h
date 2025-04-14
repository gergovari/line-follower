#pragma once

#include "motor.h"

class MotorPair {
	public:
		Motor *left;
		Motor *right;
	
		MotorPair(Motor *l, Motor *r) : left(l), right(r) {};
};
