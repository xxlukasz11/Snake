#include "timer.h"
#include "basic_allegro.h"

Timer::Timer() :
		allegroTimer(nullptr, deleteTimer) {
}

bool Timer::setTimeout(double timeoutSeconds) {
	allegroTimer = { al_create_timer(timeoutSeconds), deleteTimer };
	if (allegroTimer) {
		timeout = timeoutSeconds;
		return true;
	}
	timeout = 0;
	return false;
}

void Timer::start() {
	al_start_timer(allegroTimer.get());
}

void Timer::stop() {
	al_stop_timer(allegroTimer.get());
}

void Timer::registerAsEventSourceIn(Queue& queue) {
	al_register_event_source(queue.ptr, al_get_timer_event_source(allegroTimer.get()));
}

void Timer::deleteTimer(ALLEGRO_TIMER* timer) {
	al_destroy_timer(timer);
}
