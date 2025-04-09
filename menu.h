#pragma once

#include "common.h"
#include "screen.h"
#include "screen_manager.h"

class Menu : public Screen {
	public:
		char **names;
		void (**funcs)();
		uint size;
		uint selected = 0;

		Menu(char **n, void (**f)(), uint s) : Screen(ScreenType::MENU), names(n), funcs(f), size(s) {};

		void left(ScreenManager *manager);
		void right(ScreenManager *manager);
		void ok(ScreenManager *manager);
};
