#include "double_input.h"

#include <Arduino.h>

DoubleInput::DoubleInput(char *n, void (*c)(), double start) 
	: Screen(ScreenType::DOUBLE_INPUT), name(n), cb(c) {
	set(start);
};

void DoubleInput::set(double val) {
	whole = (int)val;
	fraction = (int)((val - whole) * pow(10, 4));
}

/* Who knew pow uses floats 
 * and it's not precise when converted to an int... */
int DoubleInput::ipow(int base, int exp)
{
	int result = 1;
	for (;;)
	{
		if (exp & 1)
			result *= base;
		exp >>= 1;
		if (!exp)
			break;
		base *= base;
	}

	return result;
}

void DoubleInput::addTo(int amount) {
	if (selected == 0) {
		whole = constrain(whole + amount, 0, 9);
	} else if (selected < 5) {
		int temp = fraction;
		for (int i = 1; i < 5; i++) {
			if (i == selected) {
				continue;
			}
			
			int n = (temp / ipow(10, 4 - i));
			if (n < 10) {
				temp -= n * ipow(10, 4 - i);
			}
		}
		temp /= ipow(10, 4 - selected);

		int multiplier = ipow(10, 4 - selected);
		if ((amount > 0 && temp < 9) || (amount < 0 && temp > 0)) {
			fraction += amount * multiplier;
		}
	} else {
		exponent = constrain(exponent + amount, -9, 9);
	}
}

void DoubleInput::left(ScreenManager *manager) {
	addTo(-1);
}

void DoubleInput::right(ScreenManager *manager) {
	addTo(1);
}

void DoubleInput::ok(ScreenManager *manager) {
	if (cb) {
		cb((whole + (double)fraction / pow(10, 4)) * pow(10, exponent));
	}
	manager->back();
}

void DoubleInput::doubleLeft(ScreenManager *manager) {
	selected = constrain(selected - 1, 0, 5);
}

void DoubleInput::doubleRight(ScreenManager *manager) {
	selected = constrain(selected + 1, 0, 5);
}
