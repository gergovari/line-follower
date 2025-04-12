#include "pid_controller.h"

#include <Arduino.h>

PIDController::PIDController(PIDParameters pa) {
	parameters = pa;

	p = new ProportionalController(parameters.target, parameters.kp);
	i = new IntegralController(parameters.ki);
	d = new DerivateController(parameters.kd);
}

PIDController::~PIDController() {
	delete p;
	delete i;
	delete d;
}

void PIDController::calculate(int in, int *out) {
	int pE = 0;
	int iE = 0;
	int dE = 0;

	if (p->kp != 0) p->calculate(in, &pE);
	if (i->ki != 0) i->calculate(pE, &iE);
	if (d->kd != 0) d->calculate(pE, &dE);

	(*out) = constrain(pE + iE + dE, lowest, highest);
	//Serial.println(*out);
}
