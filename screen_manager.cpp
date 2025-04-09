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
