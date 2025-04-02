#include "bang_raw_controller.h"

BangRawController::BangRawController(bool u) {
	useFull = u;
}

void BangRawController::calculate(int *values, uint size, int *out) {
	if (useFull) {
		(*out) = values[0] > 800 || values[1] > 800 ? -1000 : 1000;
	} else {
		(*out) = values[1] > 800 ? -1000 : 1000;
	}
}

