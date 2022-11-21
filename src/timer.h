#ifndef SRC_TIMER_H_
#define SRC_TIMER_H_

#include "allegro5/allegro.h"
#include <memory>

class Queue;

class Timer {
public:
	void start();
	void stop();
	void registerAsEventSourceIn(Queue& queue);
	static std::unique_ptr<Timer> create(double timeoutSeconds);

private:
	using AllegroTimerDeleter = void(*)(ALLEGRO_TIMER*);
	using AllegroTimerPtr = std::unique_ptr<ALLEGRO_TIMER, AllegroTimerDeleter>;

	static void deleteTimer(ALLEGRO_TIMER* timer);
	Timer(AllegroTimerPtr timerPtr);

	AllegroTimerPtr allegroTimer;
};

#endif /* SRC_TIMER_H_ */
