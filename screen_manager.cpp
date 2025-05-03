#include "screen_manager.h"

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
	display->show(current);
}

void ScreenManager::back() {
	if (previous) {
		current = previous->screen;
		display->show(current);
		
		auto *old = previous;
		previous = old->previous;
		delete old;
		count--;
	}
}

void ScreenManager::left() {
	current->left(this);
	display->show(current);
}

void ScreenManager::right() {
	current->right(this);
	display->show(current);
}

void ScreenManager::ok() {
	current->ok(this);
	display->show(current);
}

void ScreenManager::doubleLeft() {
	current->doubleLeft(this);
	display->show(current);
}

void ScreenManager::doubleRight() {
	current->doubleRight(this);
	display->show(current);
}
