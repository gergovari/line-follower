#pragma once

#include "common.h"

/* Ez egy interface, közös felülettel implementáljuk a nyers szenzort 
 * és majd kompozitáljuk egy kalibrációs/normalizálós szenzor objektbe. */
class Sensor {
	public:
		/* Ezen range-n belül reportolhat a szenzor. */
		uint lowest;
		uint highest;

		/* A megadott szenzor értékét olvassa ki. */
		virtual uint get();
};
