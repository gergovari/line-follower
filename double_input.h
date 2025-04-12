#pragma once

#include "common.h"

#include "screen.h"
#include "screen_manager.h"

class DoubleInput : public Screen {
	private:
		void addTo(int amount);
		int ipow(int base, int exponent);
	public:
		int whole = 1;
		int fraction = 0;
		int exponent = 0;

		uint selected = 0;
		
		char *name;
		void (*cb)(double in);

		DoubleInput(char *n, void (*c)(), double start);
		DoubleInput(char *n, void (*c)()) 
			: Screen(ScreenType::DOUBLE_INPUT), name(n), cb(c) {};

		void left(ScreenManager *manager);
		void right(ScreenManager *manager);
		void ok(ScreenManager *manager);

		void doubleLeft(ScreenManager *manager);
		void doubleRight(ScreenManager *manager);
};
