#include "appContext.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include "errMsg.hpp"

constexpr int DISPLAY_WIDTH = 810;
constexpr int DISPLAY_HEIGHT = 510;
constexpr int MAIN_FONT_SIZE= 24;
constexpr double FRAME_RATE_INTERVAL_SECONDS = 0.06;
constexpr const char* DISPLAY_NAME = "Snake";
constexpr const char* MAIN_FONT_NAME = "Arial";
constexpr const char* MAIN_FONT_FILE_NAME = "arial.ttf";
constexpr const char* ERROR_FILE = "error.log";

bool AppContext::initialize() {
	if (!initDisplay()) {
		errMsg r("Failed to init display");
		r.print(ERROR_FILE);
		return false;
	}

	if (!loadMainFont()) {
		errMsg r("Failed to load main font");
		r.print(ERROR_FILE);
		return false;
	}

	if (!initFrameRateTimer()) {
		errMsg r("Failed to init timer");
		r.print(ERROR_FILE);
		return false;
	}

	registerEventSources();
	return true;
}

bool AppContext::initDisplay() {
	bool initResult = display.init(DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_NAME);
	if (!initResult) {
		return initResult;
	}

	ALLEGRO_MONITOR_INFO monitor;
	al_get_monitor_info(0, &monitor);
	al_set_window_position(display.ptr, (monitor.x2 - monitor.x1 - display.width) / 2,
			(monitor.y2 - monitor.y1 - display.height) / 2);
	return true;
}

bool AppContext::loadMainFont() {
	return font.add(MAIN_FONT_NAME, MAIN_FONT_SIZE, MAIN_FONT_FILE_NAME);
}

bool AppContext::initFrameRateTimer() {
	return timer.init(FRAME_RATE_INTERVAL_SECONDS);
}

void AppContext::registerEventSources() {
	queue.register_keyboard();
	queue.register_source(display.ptr);
	queue.register_source(timer.ptr);
}

void AppContext::flushEventQueue() {
	al_flush_event_queue(queue.ptr);
}

void AppContext::startFrameRateUpdates() {
	al_start_timer(timer.ptr);
}

void AppContext::stopFrameRateUpdates() {
	al_stop_timer(timer.ptr);
}

ALLEGRO_FONT* AppContext::getMainFont() const {
	return font[MAIN_FONT_NAME];
}

float AppContext::getFrameRateIntervalSeconds() const {
	return FRAME_RATE_INTERVAL_SECONDS;
}

const Display& AppContext::getDisplay() const {
	return display;
}

void AppContext::waitForEvent(ALLEGRO_EVENT& event) {
	al_wait_for_event(queue.ptr, &event);
}

bool init_alllegro_modules() {
	try {
		if (!al_init()) {
			throw errMsg("Failed to initialize allegro");
		}
		if (!al_install_audio()) {
			throw errMsg("Failed to install audio");
		}
		if (!al_init_acodec_addon()) {
			throw errMsg("Failed to initialize acodec addon");
		}
		if (!al_init_primitives_addon()) {
			throw errMsg("Failed to initialize primitives addon");
		}
		if (!al_install_keyboard()) {
			throw errMsg("Failed to install keyboard");
		}

		al_init_font_addon();
		if (!al_init_ttf_addon()) {
			throw errMsg("Failed to initialize ttf addon");
		}
	}
	catch (errMsg& r) {
		r.print(ERROR_FILE);
		return false;
	}

	ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
	al_append_path_component(path, "../resources");
	al_change_directory(al_path_cstr(path, '/'));
	al_destroy_path(path);
	return true;
}
