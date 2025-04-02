#include "bang_controller.h"

void BangController::calculate(int in, int *out) {
	(*out) = in < 0 ? -1000 : 1000;
}

