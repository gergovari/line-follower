#include "menu.h"

#include <Arduino.h>

void Menu::left(ScreenManager *manager) {
	selected = constrain(selected - 1, 0, size - 1);
}

void Menu::right(ScreenManager *manager) {
	selected = constrain(selected + 1, 0, size - 1);
}

void Menu::ok(ScreenManager *manager) {
	auto func = funcs[constrain(selected, 0, size - 1)];
	if (func) func();
}

void Popup::ok(ScreenManager *manager) {
	if (func) func();
	manager->back();
}

ScreenManager::~ScreenManager() {
	auto *node = previous;
	while (node != nullptr) {
		node = node->previous; 
		delete previous;
	}
}

void ScreenManager::push(Screen *screen) {
	previous = new ScreenNode(previous, current);
	count++;

	current = screen;
}

void ScreenManager::back() {
	if (previous) {
		current = previous->screen;
		
		auto *old = previous;
		previous = old->previous;
		delete old;
		count--;
	}
}

void ScreenManager::left() {
	current->left(this);
}

void ScreenManager::right() {
	current->right(this);
}

void ScreenManager::ok() {
	current->ok(this);
}
