#include "menu.h"

#include <Arduino.h>

void Menu::left(ScreenManager *manager) {
	selected = constrain(selected - 1, 0, size - 1);
}

void Menu::doubleLeft(ScreenManager *manager) {
	selected = 0;
}

void Menu::right(ScreenManager *manager) {
	selected = constrain(selected + 1, 0, size - 1);
}

void Menu::doubleRight(ScreenManager *manager) {
	selected = size - 1;
}

void Menu::ok(ScreenManager *manager) {
	auto func = funcs[constrain(selected, 0, size - 1)];
	if (func) func();
}
