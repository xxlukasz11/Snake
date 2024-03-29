#include "appContext.h"
#include "errorMsg.h"
#include "allegro-cpp/color.h"

// TODO: read these values from configuration file
constexpr int DISPLAY_WIDTH_RASTERS = 40;
constexpr int DISPLAY_HEIGHT_RASTERS = 25;
constexpr int RASTER_SIZE = 30;
constexpr int MAIN_FONT_SIZE = 24;
constexpr double FRAME_RATE_INTERVAL_SECONDS = 0.06;
constexpr const char* DISPLAY_NAME = "Snake";
constexpr const char* MAIN_FONT_FILE_NAME = "arial.ttf";
constexpr const char* ERROR_FILE = "error.log";
constexpr const char* AUDIO_SAMPLE_FILE = "sample.wav";
static const allegrocpp::Color FONT_COLOR = allegrocpp::Color::rgb(0, 0, 0);

using allegrocpp::AudioSample;
using allegrocpp::Timer;
using allegrocpp::Font;
using allegrocpp::Display;
using allegrocpp::TextWriter;
using allegrocpp::Event;

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

	textWriter = std::make_unique<TextWriter>(*display, *font, FONT_COLOR);
	registerEventSources();
	return true;
}

bool AppContext::initDisplay() {
	allegrocpp::DisplayInitParams displayParams;
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
	frameRateTimer = Timer::create(FRAME_RATE_INTERVAL_SECONDS);
	return frameRateTimer.operator bool();
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
	queue.registerTimer(*frameRateTimer);
	queue.registerDisplay(*display);
}

void AppContext::startFrameRateUpdates() {
	return frameRateTimer->start();
}

TextWriter& AppContext::getTextWriter() const {
	return *textWriter;
}

void AppContext::stopApp() {
	runningFlag = false;
}

bool AppContext::shouldBeRunning() const {
	return runningFlag;
}

const Display& AppContext::getDisplay() const {
	return *display;
}

const AudioSample& AppContext::getErrorAudioSample() const {
	return *errorSample;
}

Event AppContext::waitForEvent() {
	return queue.waitForEvent();
}
