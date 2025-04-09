#include "double_input.h"

#include <Arduino.h>

void DoubleInput::left(ScreenManager *manager) {
	if (selected < 5) {
		in -= 1. / pow(10, selected);
	} else {
		//in /= pow(10, -selected);
	}
	//in = constrain(in, 0, 1);
}

void DoubleInput::right(ScreenManager *manager) {
	if (selected < 5) {
		in += 1. / pow(10, selected);
	} else {
		//in *= pow(10, -selected);
	}
	//in = constrain(in, 0, 1);
}

void DoubleInput::ok(ScreenManager *manager) {
	if (cb) {
		cb(in);
	}
}

void DoubleInput::doubleLeft(ScreenManager *manager) {
	Serial.print("left, selected: ");
	Serial.println(selected);
	selected--;
}

void DoubleInput::doubleRight(ScreenManager *manager) {
	Serial.print("right, selected: ");
	Serial.println(selected);
	selected++;
}
