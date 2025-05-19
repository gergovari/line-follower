#include "configuration.h"

// TODO: load from EEPROM
void Configuration::load() {
	target = 0;
	p = 0;
	i = 0;
	d = 0;
}

// TODO: save to EEPROM
void Configuration::save() {}

void Configuration::apply(PID3Controller *pid) {
	auto *parameters = &pid->parameters;

	parameters->target = target;
	parameters->kp = p;
	parameters->ki = i;
	parameters->kd = d;
}
