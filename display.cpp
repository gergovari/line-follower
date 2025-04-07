#include "display.h"

#include <Arduino.h>

Display::Display() {
	lcd = new LiquidCrystal_I2C(0x27, 20, 4);
}

Display::~Display() {
	delete lcd;
}

void Display::begin() {
	lcd->init();
	lcd->backlight();
	lcd->clear();
}

void Display::clear() {
	lcd->clear();
}

void Display::blink(bool state) {
	if (state) {
		lcd->blink();
	} else {
		lcd->noBlink();
	}
}

void Display::blink() {
	blink(true);
}

void Display::write(uint x, uint y, char *m) {
	lcd->setCursor(x, y);
	lcd->print(m);
}

void Display::show(Menu *menu) {
	if (menu->size > 4) return;
	lcd->clear();

	for (uint i = 0; i < menu->size; i++) {
		char *name = menu->names[i];
		uint longestSecondHalf = menu->size > 2 
				? max(strlen(menu->names[2]), strlen(menu->names[3])) 
				: 0;

		uint x = i < 2 ? 0 : 15 - longestSecondHalf;
		uint y = i < 2 ? i : i - 2;

		write(x, y, ">");
		write(x + 1, y, menu->names[i]);
	}
	
	uint i = menu->selected;
	uint longestSecondHalf = menu->size > 2 
			? max(strlen(menu->names[2]), strlen(menu->names[3])) 
			: 0;
	uint x = i < 2 ? 0 : 15 - longestSecondHalf;
	uint y = i < 2 ? i : i - 2;
	lcd->setCursor(x, y);
	lcd->blink();
}
