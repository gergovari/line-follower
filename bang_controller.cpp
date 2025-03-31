#include "bang_controller.h"

BangController::BangController(bool u) {
	useFull = u;
}

void BangController::calculate(int in, int *out) {
	(*out) = in < 0 ? -1000 : 1000;
}

