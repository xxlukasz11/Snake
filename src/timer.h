#ifndef SRC_TIMER_H_
#define SRC_TIMER_H_

#include "allegro5/allegro.h"
#include <memory>

class Queue;

class Timer {
public:
	Timer();
	bool setTimeout(double timeoutSeconds);
	void start();
	void stop();
	void registerAsEventSourceIn(Queue& queue);

private:
	using TimerDeleter = void(*)(ALLEGRO_TIMER*);
	static void deleteTimer(ALLEGRO_TIMER* timer);
	std::unique_ptr<ALLEGRO_TIMER, TimerDeleter> allegroTimer;
	double timeout{ 0 };
};

#endif /* SRC_TIMER_H_ */
