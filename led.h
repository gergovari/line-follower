#pragma once

#include "common.h"

/* Infrared LED-ek vezérlése. */
class Led {
	private:
		Pin pin;
	public:
		Led(Pin p);
		
		/* A megadott LED (ki/be) állapotát állítja be. */
		void set(bool state);
};
