#pragma once

#include "common.h"
#include "motor_pair.h"
#include "motor.h"

class Steering {
	private:
		Motor *left;
		Motor *right;
	
	public:
		signed int lowest = -1000;
		signed int highest = 1000;

		Steering(MotorPair *motors) 
			: left(motors->left), right(motors->right) {};

		void setTarget(signed int t);
		void stop();
};
