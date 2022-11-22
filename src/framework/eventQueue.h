#ifndef SRC_EVENTQUEUE_H_
#define SRC_EVENTQUEUE_H_

#include <allegro5/allegro.h>
#include <memory>

namespace framework {

class Timer;
class Display;

class EventQueue {
public:
	EventQueue();
	void registerKeyboard();
	void registerMouse();
	void registerTimer(const Timer& timer);
	void registerDisplay(const Display& display);
	void flushEvents();
	void waitForEvent(ALLEGRO_EVENT& outEvent);
	ALLEGRO_EVENT_QUEUE* getAllegroQueuePtr();

private:
	using AllegroEventQueueDeleter = void(*)(ALLEGRO_EVENT_QUEUE* queue);
	using AllegroEventQueuePtr = std::unique_ptr<ALLEGRO_EVENT_QUEUE, AllegroEventQueueDeleter>;

	static void destroyEventQueue(ALLEGRO_EVENT_QUEUE* queue);

	AllegroEventQueuePtr allegroEventQueue;
};

} // namespace framework

#endif /* SRC_EVENTQUEUE_H_ */
