#pragma once

#include "common.h"
#include "screen.h"
#include "display.h"

class ScreenNode {
	public:
		ScreenNode *previous;
		Screen *screen;
		
		ScreenNode(ScreenNode *p, Screen *s) : previous(p), screen(s) {};
};

class Display;

class ScreenManager {
	private:
		ScreenNode *previous = nullptr;
		uint count = 0;
		
		Display *display;
	public:
		Screen *current;
		ScreenManager(Display *d) : display(d) {};
		~ScreenManager();
		
		void push(Screen *screen);
		void back();

		void left();
		void right();
		void ok();

		void doubleLeft();
		void doubleRight();
};
