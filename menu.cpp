#include "menu.h"

#include <Arduino.h>

void Menu::left() {
	selected = constrain(selected - 1, 0, size - 1);
}

void Menu::right() {
	selected = constrain(selected + 1, 0, size - 1);
}

void Menu::execute() {
	auto func = funcs[constrain(selected, 0, size - 1)];
	if (func) {
		func();
	}
}

MenuManager::~MenuManager() {
	MenuNode *node = previous;
	while (node != nullptr) {
		node = node->previous; 
		delete previous;
	}
}

void MenuManager::push(Menu *menu) {
	previous = new MenuNode(previous, current);
	count++;

	current = menu;
}

void MenuManager::back() {
	if (previous) {
		current = previous->menu;
		
		MenuNode *old = previous;
		previous = old->previous;
		delete old;
		count--;
	}
}
