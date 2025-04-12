#pragma once

#include "pid_controller.h"

class Configuration {
	public:
		double target = 0;
		double p = 0;
		double i = 0;
		double d = 0;
		
		Configuration(double t, double kp, double ki, double kd) 
			: target(t), p(kp), i(ki), d(kd) {
				load();
			};

		void load();
		void save();
		void apply(PIDController *pid);
};
