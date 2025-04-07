#pragma once

#include "menu.h"

class MenuConsumer {
	public:
		virtual void show(Menu *menu);
};
