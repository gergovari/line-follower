#pragma once

#include "common.h"

enum class Direction { FORWARD, BACKWARD };

class Motor {
	private:
		uint inLowest = 0;
		uint inHighest = 1000;
		
		/* FIXME: assuming 8-bit PWM output */
		uint outLowest = 255 / 2;
		uint outHighest = 255;

		Pin forward;
		Pin backward;
		Pin speed;
	
	public:
		Motor(Pin f, Pin b, Pin s);
		
		void setSpeed(uint s);
};
