#pragma once

#include "common.h"

class Menu {
	public:
		char **names;
		void (**funcs)();
		uint size;

		uint selected = 0;

		Menu(char **n, void (**f)(), uint s) : names(n), funcs(f), size(s) {};

		void left();
		void right();
		void execute();
};
