#include "led.h"

#include <Arduino.h>

Led::Led(Pin p) {
	pin = p;

	pinMode(pin, OUTPUT);

	/* Kezdjük bekapcsolva, elvileg úgy se fogunk ezzel babrálni. 
	 * "De igazából nem tudom mennyi haszna lenne." */
	set(true);
}

void Led::set(bool state) {
	digitalWrite(pin, state);
}
