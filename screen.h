#pragma once

enum class ScreenType {
	MENU,
	POPUP
};

class ScreenManager;

class Screen {
	public:
		ScreenType type;

		virtual void left(ScreenManager *manager) = 0;
		virtual void right(ScreenManager *manager) = 0;
		virtual void ok(ScreenManager *manager) = 0;

		Screen(ScreenType t) : type(t) {};
};
