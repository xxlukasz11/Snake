#include "app.hpp"

constexpr int DISPLAY_WIDTH = 810;
constexpr int DISPLAY_HEIGHT = 510;

bool App::initDisplay(const std::string& displayName) {
	bool initResult = display.init(DISPLAY_WIDTH, DISPLAY_HEIGHT, displayName.c_str());
	if (!initResult) {
		return initResult;
	}

	al_get_monitor_info(0, &monitor);
	al_set_window_position(display.ptr, (monitor.x2 - monitor.x1 - display.width) / 2, (monitor.y2 - monitor.y1 - display.height) / 2);
	return true;
}
