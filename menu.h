#pragma once

#include "common.h"

enum class ScreenType {
	MENU,
	POPUP
};

class ScreenManager;

class Screen {
	public:
		ScreenType type;

		virtual void left(ScreenManager *manager) = 0;
		virtual void right(ScreenManager *manager) = 0;
		virtual void ok(ScreenManager *manager) = 0;

		Screen(ScreenType t) : type(t) {};
};

class Popup : public Screen {
	public:
		char* msg;
		void (*func)();

		Popup(char *m, void (*f)()) : Screen(ScreenType::POPUP), msg(m), func(f) {};
		Popup(char *m) : Screen(ScreenType::POPUP), msg(m), func(nullptr) {};

		void left(ScreenManager *manager) {};
		void right(ScreenManager *manager) {};
		void ok(ScreenManager *manager);
};

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

class ScreenNode {
	public:
		ScreenNode *previous;
		Screen *screen;
		
		ScreenNode(ScreenNode *p, Screen *s) : previous(p), screen(s) {};
};

class ScreenManager {
	private:
		ScreenNode *previous = nullptr;
		uint count = 0;

	public:
		Screen *current;
		~ScreenManager();
		
		void push(Screen *screen);
		void back();

		void left();
		void right();
		void ok();
};
