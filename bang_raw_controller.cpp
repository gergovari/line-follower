#include "bang_raw_controller.h"

BangRawController::BangRawController(bool u) {
	useFull = u;
}

void BangRawController::calculate(int *values, uint size, int *out) {
	if (useFull) {
		// TODO
	} else {
		(*out) = values[1] > 800 ? -1000 : 1000;
	}
}

