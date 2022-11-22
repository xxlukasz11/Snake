#ifndef SRC_FRAMEWORK_TIMER_H_
#define SRC_FRAMEWORK_TIMER_H_

#include "allegro5/allegro.h"
#include <memory>

namespace framework {

class EventQueue;

class Timer {
	friend class EventQueue;
public:
	void start();
	void stop();
	bool isSourceOf(const ALLEGRO_EVENT& event) const;
	static std::unique_ptr<Timer> create(double timeoutSeconds);

private:
	using AllegroTimerDeleter = void(*)(ALLEGRO_TIMER*);
	using AllegroTimerPtr = std::unique_ptr<ALLEGRO_TIMER, AllegroTimerDeleter>;

	static void deleteTimer(ALLEGRO_TIMER* timer);
	Timer(AllegroTimerPtr timerPtr);

	AllegroTimerPtr allegroTimer;
};

} // namespace framework

#endif /* SRC_FRAMEWORK_TIMER_H_ */
