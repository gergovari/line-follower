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

class MenuNode {
	public:
		MenuNode *previous;
		Menu *menu;
		
		MenuNode(MenuNode *p, Menu *m) : previous(p), menu(m) {};
};

class MenuManager {
	private:
		MenuNode *previous = nullptr;
		uint count = 0;

	public:
		Menu *current;
		~MenuManager();
		
		void push(Menu *menu);
		void back();
};
