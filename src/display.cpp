#include "display.h"

#include "eventQueue.h"

void Display::destroyDisplay(ALLEGRO_DISPLAY* display) {
	al_destroy_display(display);
}

Display::Display(AllegroDisplayPtr allegrodisplay, const DisplayInitParams& displayInitParams) :
		allegroDisplay(std::move(allegrodisplay)),
		rasterSize(displayInitParams.rasterSizePixels),
		widthRasters(displayInitParams.numHorizontalRasters),
		heightRasters(displayInitParams.numVerticalRasters),
		widthPixels(widthRasters * rasterSize),
		heightPixels(heightRasters * rasterSize) {
}

void Display::placeAtScreenCenter() {
	ALLEGRO_MONITOR_INFO monitor;
	al_get_monitor_info(0, &monitor);
	al_set_window_position(allegroDisplay.get(), (monitor.x2 - monitor.x1 - widthPixels) / 2,
			(monitor.y2 - monitor.y1 - heightPixels) / 2);
}

void Display::registerAsEventSourceIn(EventQueue& queue) {
	al_register_event_source(queue.getAllegroQueuePtr(), al_get_display_event_source(allegroDisplay.get()));
}

int Display::getRasterSize() const {
	return rasterSize;
}

int Display::getWidthPixels() const {
	return widthPixels;
}

int Display::getHeightPixels() const {
	return heightPixels;
}

int Display::getWidthRasters() const {
	return widthRasters;
}

int Display::getHeightRasters() const {
	return heightRasters;
}

std::unique_ptr<Display> Display::create(const DisplayInitParams& displayInitParams) {
	auto widthPixels = displayInitParams.numHorizontalRasters * displayInitParams.rasterSizePixels;
	auto heightPixels = displayInitParams.numVerticalRasters * displayInitParams.rasterSizePixels;

	AllegroDisplayPtr displayPtr{ al_create_display(widthPixels, heightPixels), destroyDisplay };
	if (!displayPtr) {
		return nullptr;
	}
	al_set_window_title(displayPtr.get(), displayInitParams.windowName.c_str());
	return std::unique_ptr<Display>(new Display(std::move(displayPtr), displayInitParams));
}
