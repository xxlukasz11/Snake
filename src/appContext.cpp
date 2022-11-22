#include "appContext.h"

#include "errorMsg.h"

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

using framework::AudioSample;
using framework::Timer;
using framework::Font;
using framework::Display;

bool AppContext::initialize() {
	if (!initDisplay()) {
		ErrorMsg r("Failed to init display");
		r.print(ERROR_FILE);
		return false;
	}

	if (!loadMainFont()) {
		ErrorMsg r("Failed to load main font");
		r.print(ERROR_FILE);
		return false;
	}

	if (!initFrameRateTimer()) {
		ErrorMsg r("Failed to init timer");
		r.print(ERROR_FILE);
		return false;
	}

	if (!loadAudioSamples()) {
		ErrorMsg r("Failed to load audio samples");
		r.print(ERROR_FILE);
		return false;
	}

	registerEventSources();
	return true;
}

bool AppContext::initDisplay() {
	framework::DisplayInitParams displayParams;
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
	font = Font::loadFromTtfFile(MAIN_FONT_FILE_NAME, MAIN_FONT_SIZE);
	return font.operator bool();
}

bool AppContext::initFrameRateTimer() {
	snakeMovementTimer = Timer::create(FRAME_RATE_INTERVAL_SECONDS);
	return snakeMovementTimer.operator bool();
}

bool AppContext::loadAudioSamples() {
	if (!al_reserve_samples(1)) {
		return false;
	}
	errorSample = AudioSample::loadFromFile(AUDIO_SAMPLE_FILE);
	return errorSample.operator bool();
}

void AppContext::registerEventSources() {
	queue.registerKeyboard();
	queue.registerTimer(*snakeMovementTimer);
	queue.registerDisplay(*display);
}

Timer& AppContext::getSnakeMovementTimer() const {
	return *snakeMovementTimer;
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

const Display& AppContext::getDisplay() const {
	return *display;
}

const AudioSample& AppContext::getErrorAudioSample() const {
	return *errorSample;
}

void AppContext::waitForEvent(ALLEGRO_EVENT& event) {
	queue.waitForEvent(event);
}
