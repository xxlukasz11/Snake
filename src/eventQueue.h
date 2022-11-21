#ifndef SRC_EVENTQUEUE_H_
#define SRC_EVENTQUEUE_H_

#include <allegro5/allegro.h>
#include <memory>

class EventQueue {
public:
	EventQueue();
	void register_keyboard();
	void register_mouse();
	void flushEvents();
	void waitForEvent(ALLEGRO_EVENT& outEvent);
	ALLEGRO_EVENT_QUEUE* getAllegroQueuePtr();

private:
	using AllegroEventQueueDeleter = void(*)(ALLEGRO_EVENT_QUEUE* queue);
	using AllegroEventQueuePtr = std::unique_ptr<ALLEGRO_EVENT_QUEUE, AllegroEventQueueDeleter>;

	static void destroyEventQueue(ALLEGRO_EVENT_QUEUE* queue);

	AllegroEventQueuePtr allegroEventQueue;
};

#endif /* SRC_EVENTQUEUE_H_ */
