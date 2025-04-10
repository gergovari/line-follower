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
	clear();
}

void Display::clear() {
	lcd->setCursor(0, 0);
	blink(false);
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

void Display::show(Screen *screen) {
	clear();
	switch (screen->type) {
		case ScreenType::MENU:
			show((Menu*)screen);
			break;
		case ScreenType::POPUP:
			show((Popup*)screen);
			break;
		case ScreenType::DOUBLE_INPUT:
			show((DoubleInput*)screen);
			break;
		default:
			return;
	}
}

void Display::show(Menu *menu) {
	if (menu->size > 4) return;

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

void Display::show(Popup *popup) {
	// FIXME: unsafe I guess
	write(0, 0, popup->msg);
	write(0, 1, ">DISMISS");
	lcd->setCursor(0, 1);
	blink();
}

void Display::show(DoubleInput *input) {
}
