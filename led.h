#pragma once

#include "common.h"

class Led {
	private:
		Pin pin;
	public:
		Led(Pin p, bool start);
		Led(Pin p) : Led(p, true) {};
		
		void set(bool state);
};
