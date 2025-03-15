#pragma once

#include "common.h"

enum class Direction { FORWARD, BACKWARD, BRAKE };

class Motor {
	private:
		
		/* FIXME: assuming 8-bit PWM output */
		uint outLowest = 255 / 2;
		uint outHighest = 255;

		Pin forward;
		Pin backward;
		Pin speed;
		
		void setDirection(Direction dir);
	public:
		signed int highest = 1000;
		signed int lowest = -1000;

		Motor(Pin f, Pin b, Pin s);
		
		void setSpeed(signed int s);
};
