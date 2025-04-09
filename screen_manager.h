#pragma once

#include "common.h"
#include "screen.h"

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
