#pragma once

#include "screen.h"
#include "screen_manager.h"

class Popup : public Screen {
	public:
		char* msg;
		void (*func)();

		Popup(char *m, void (*f)()) : Screen(ScreenType::POPUP), msg(m), func(f) {};
		Popup(char *m) : Screen(ScreenType::POPUP), msg(m), func(nullptr) {};

		void left(ScreenManager *manager) {};
		void right(ScreenManager *manager) {};
		void ok(ScreenManager *manager);

		void doubleLeft(ScreenManager *manager) {};
		void doubleRight(ScreenManager *manager) {};
};
