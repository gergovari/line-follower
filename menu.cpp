#include "menu.h"

#include <Arduino.h>

void Menu::left() {
	selected = constrain(selected - 1, 0, size - 1);
}

void Menu::right() {
	selected = constrain(selected + 1, 0, size - 1);
}

void Menu::execute() {
	funcs[constrain(selected, 0, size - 1)]();
}
