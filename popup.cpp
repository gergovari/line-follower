#include "popup.h"

void Popup::ok(ScreenManager *manager) {
	if (func) func();
	manager->back();
}
