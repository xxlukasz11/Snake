#include "eventQueue.h"

EventQueue::EventQueue() :
		allegroEventQueue(al_create_event_queue(), destroyEventQueue) {
}

void EventQueue::flushEvents() {
	al_flush_event_queue(allegroEventQueue.get());
}

void EventQueue::waitForEvent(ALLEGRO_EVENT& outEvent) {
	al_wait_for_event(allegroEventQueue.get(), &outEvent);
}

void EventQueue::destroyEventQueue(ALLEGRO_EVENT_QUEUE* queue) {
	al_destroy_event_queue(queue);
}

void EventQueue::register_keyboard() {
	// TODO: unify event registration with timer and display
	al_register_event_source(allegroEventQueue.get(), al_get_keyboard_event_source());
}
void EventQueue::register_mouse() {
	al_register_event_source(allegroEventQueue.get(), al_get_mouse_event_source());
}

ALLEGRO_EVENT_QUEUE* EventQueue::getAllegroQueuePtr() {
	return allegroEventQueue.get();
}
