#include <Arduino.h>

struct LedPinmux {
	unsigned int first[2];
	unsigned int second[2];
	unsigned int third[2];
	unsigned int fourth[2];
};

struct LedCalibration {
	unsigned int low;
	unsigned int high;
};

enum class Led {
	FIRST = 0, 
	SECOND = 1, 
	THIRD = 2, 
	FOURTH = 3
};

class LedDriver {
	public:
		unsigned int pins[8];
		struct LedCalibration calibration;

		LedDriver(struct LedPinmux pinmux, struct LedCalibration c);
		void setState(Led led, bool state);
		bool getState(Led led);

	private:
		unsigned int readVal(Led led);
};

LedDriver::LedDriver(struct LedPinmux pinmux, struct LedCalibration c) {
		pins[4] = {
			pinmux.first[0], 
			pinmux.second[0],
			pinmux.third[0], 
			pinmux.fourth[0],

			pinmux.first[1], 
			pinmux.second[1],
			pinmux.third[1], 
			pinmux.fourth[1]
		};
		calibration = c;

		for (const auto pin : pins) {
			pinMode(pin, OUTPUT);
		}
}

void LedDriver::setState(Led led, bool state) {
	digitalWrite(pins[led], state);
}

bool LedDriver::getState(Led led) {
	unsigned int val = readVal(led);

	if (val >= calibration.high) {
		return true;
	} else if (val =< calibration.low) {
		return false;
	} else {
		// TODO: what to do?
		return false;
	}
}

unsigned int LedDriver::readVal(Led led) {
	return analogRead(pins[4 + led]);
}

class LedController {

};

LedDriver led(
	LedPinmux{
		{ 8, A0 },
		{ 9, A1 },
		{ 10, A2 },
		{ 11, A3 }
	}, 
	
	// TODO: calibration
	LedCalibration{
		30,
		240
	}
);

void setup()
{
	Serial.begin(9600);
}

void loop()
{

}
