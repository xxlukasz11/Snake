#include "appContext.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <memory>
#include "errMsg.hpp"

constexpr int DISPLAY_WIDTH_RASTERS = 54;
constexpr int DISPLAY_HEIGHT_RASTERS = 34;
constexpr int RASTER_SIZE = 15;
constexpr int MAIN_FONT_SIZE = 24;
constexpr double FRAME_RATE_INTERVAL_SECONDS = 0.06;
constexpr const char* DISPLAY_NAME = "Snake";
constexpr const char* MAIN_FONT_NAME = "Arial";
constexpr const char* MAIN_FONT_FILE_NAME = "arial.ttf";
constexpr const char* ERROR_FILE = "error.log";
constexpr const char* AUDIO_SAMPLE_FILE = "sample.wav";

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

	if (!loadAudioSamples()) {
		errMsg r("Failed to load audio samples");
		r.print(ERROR_FILE);
		return false;
	}

	registerEventSources();
	return true;
}

bool AppContext::initDisplay() {
	DisplayInitParams displayParams;
	displayParams.rasterSizePixels = RASTER_SIZE;
	displayParams.numHorizontalRasters = DISPLAY_WIDTH_RASTERS;
	displayParams.numVerticalRasters = DISPLAY_HEIGHT_RASTERS;
	displayParams.windowName = DISPLAY_NAME;

	display = Display::create(displayParams);
	if (!display) {
		return false;
	}
	display->placeAtScreenCenter();
	return true;
}

bool AppContext::loadMainFont() {
	font = Font::loadFromFile(MAIN_FONT_FILE_NAME, MAIN_FONT_SIZE);
	return font.operator bool();
}

bool AppContext::initFrameRateTimer() {
	timer = Timer::create(FRAME_RATE_INTERVAL_SECONDS);
	return timer.operator bool();
}

bool AppContext::loadAudioSamples() {
	if (!al_reserve_samples(1)) {
		return false;
	}
	errorSample = AudioSample::loadFromFile(AUDIO_SAMPLE_FILE);
	return errorSample.operator bool();
}

void AppContext::registerEventSources() {
	queue.register_keyboard();
	display->registerAsEventSourceIn(queue);
	timer->registerAsEventSourceIn(queue);
}

void AppContext::flushEventQueue() {
	queue.flushEvents();
}

void AppContext::startFrameRateUpdates() {
	timer->start();
}

void AppContext::stopFrameRateUpdates() {
	timer->stop();
}

void AppContext::stopApp() {
	runningFlag = false;
}

bool AppContext::getRunningFlag() const {
	return runningFlag;
}

const Font& AppContext::getMainFont() const {
	return *font;
}

float AppContext::getFrameRateIntervalSeconds() const {
	return FRAME_RATE_INTERVAL_SECONDS;
}

const Display& AppContext::getDisplay() const {
	return *display;
}

const AudioSample& AppContext::getErrorAudioSample() const {
	return *errorSample;
}

void AppContext::waitForEvent(ALLEGRO_EVENT& event) {
	queue.waitForEvent(event);
}

bool app_init_alllegro_modules() {
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
	} catch (errMsg& r) {
		r.print(ERROR_FILE);
		return false;
	}

	ALLEGRO_PATH* path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
	al_append_path_component(path, "../resources");
	al_change_directory(al_path_cstr(path, '/'));
	al_destroy_path(path);
	return true;
}
