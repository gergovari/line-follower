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

void Configuration::apply(PIDController *pid) {
	pid->p->kp = p;
	pid->p->target = target;
	pid->i->ki = i;
	pid->d->kd = d;
}
