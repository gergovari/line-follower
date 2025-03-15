#include "raw_sensor.h"

#include <Arduino.h>

RawSensor::RawSensor(Pin p) {
	pin = p;

	/* FIXME: assuming 10-bit ADC, I could hack together a check 
	 * as the Arduino library provides none to get it 
	 * but it's out of scope. 
	 * Still, as we constrain the output this could be problematic on another board. */
	lowest = 0;
	highest = 1023;

	pinMode(pin, INPUT);
}

uint RawSensor::get() {
	/* Ez egy nyers érték, változik környezettel 
	 * és akár fototranzisztoronként a jelentése. */
	return constrain(analogRead(pin), lowest, highest);
}

