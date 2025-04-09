#pragma once

#include <LiquidCrystal_I2C.h>

#include "common.h"
#include "menu.h"
#include "popup.h"
#include "double_input.h"

class Display {
	private:
		LiquidCrystal_I2C *lcd;

	public:
		Display();
		~Display();
		
		void begin();
		void clear();
		void blink(bool state);
		void blink();
		void write(uint x, uint y, char *m);

		void show(Screen *screen);
		void show(Menu *menu);
		void show(Popup *popup);
		void show(DoubleInput *input);
};
