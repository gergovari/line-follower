#pragma once

#include <OneButton.h>
#include "common.h"

class ButtonConfig {
	public:
		Pin pin;
		void (*click)();
		void (*hold)();
		
		ButtonConfig(Pin p, void (*c)(), void (*h)()) : pin(p), click(c), hold(h) {}
		ButtonConfig(Pin p, void (*c)()) : pin(p), click(c), hold(nullptr) {}
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
