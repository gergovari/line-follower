#pragma once

#include "common.h"

enum class Direction { FORWARD, BACKWARD, BRAKE };

/* Motor irány és sebesség vezérlése. */
class Motor {
	private:
		
		/* FIXME: assuming 8-bit PWM output */
		uint outLowest = 255 / 2;
		uint outHighest = 255;

		Pin forward;
		Pin backward;
		Pin speed;
		
		/* A JELORE és JHATRA pineket ez vezérli. */
		void setDirection(Direction dir);
	public:
		signed int highest = 1000;
		signed int lowest = -1000;

		Motor(Pin f, Pin b, Pin s);
		
		/* A JSEBESSEG PWM output-ot ez vezérli. */
		void setSpeed(signed int s);
};
