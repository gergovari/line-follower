#pragma once

#include <LiquidCrystal_I2C.h>

#include "common.h"
#include "menu_consumer.h"
#include "menu.h"

class Display : public MenuConsumer {
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

		void show(Menu *menu);
};
