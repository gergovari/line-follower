#include "led.h"

#include <Arduino.h>

Led::Led(Pin p, bool start) {
	pin = p;

	pinMode(pin, OUTPUT);
	set(start);
}

void Led::set(bool state) {
	digitalWrite(pin, state);
}
