#ifndef SRC_EVENTQUEUE_H_
#define SRC_EVENTQUEUE_H_

#include <allegro5/allegro.h>

class EventQueue {
public:
	ALLEGRO_EVENT_QUEUE* ptr;
	EventQueue();
	~EventQueue();
	void register_keyboard();
	void register_mouse();
};

#endif /* SRC_EVENTQUEUE_H_ */
