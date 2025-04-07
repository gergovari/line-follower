#pragma once

#include <OneButton.h>
#include "common.h"

class ButtonConfig {
	public:
		Pin pin;
		void (*cb)();
		
		ButtonConfig(Pin p, void (*c)()) : pin(p), cb(c) {}
};

class ConfiguredButton {
	private:
		OneButton *btn;

	public:
		ConfiguredButton(ButtonConfig c);
		~ConfiguredButton();

		void tick();
};

class Input {
	private:
		ConfiguredButton** btns;
		uint size;

	public:
		Input(ButtonConfig **c, uint s);
		~Input();

		void tick();
};
