#include "timer.h"

#include "eventQueue.h"

Timer::Timer(AllegroTimerPtr timerPtr) :
		allegroTimer(std::move(timerPtr)) {
}

void Timer::start() {
	al_start_timer(allegroTimer.get());
}

void Timer::stop() {
	al_stop_timer(allegroTimer.get());
}

void Timer::registerAsEventSourceIn(EventQueue& queue) {
	al_register_event_source(queue.ptr, al_get_timer_event_source(allegroTimer.get()));
}

void Timer::deleteTimer(ALLEGRO_TIMER* timer) {
	al_destroy_timer(timer);
}

std::unique_ptr<Timer> Timer::create(double timeoutSeconds) {
	AllegroTimerPtr timerPtr{ al_create_timer(timeoutSeconds), deleteTimer };
	if (!timerPtr) {
		return nullptr;
	}
	return std::unique_ptr<Timer>(new Timer(std::move(timerPtr)));
}
