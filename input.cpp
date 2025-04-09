#include "input.h"

ConfiguredButton::ConfiguredButton(ButtonConfig c) {
	btn = new OneButton(c.pin, true, true);

	btn->attachClick(c.click);
	btn->attachLongPressStart(c.hold);
	btn->attachDoubleClick(c.doubl);
}

ConfiguredButton::~ConfiguredButton() {
	delete btn;
}

void ConfiguredButton::tick() {
	btn->tick();
}

Input::Input(ButtonConfig **c, uint s) : size(s) {
	btns = malloc(size * sizeof(ConfiguredButton*));

	for (uint i = 0; i < size; i++) {
		btns[i] = new ConfiguredButton(*(c[i]));
	}
}

Input::~Input() {
	for (uint i = 0; i < size; i++) {
		delete btns[i];
	}
}

void Input::tick() {
	for (uint i = 0; i < size; i++) {
		btns[i]->tick();
	}
}
