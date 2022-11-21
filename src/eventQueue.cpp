#include "eventQueue.h"

EventQueue::EventQueue() {
	ptr = al_create_event_queue();
}

EventQueue::~EventQueue() {
	if (ptr) {
		al_destroy_event_queue(ptr);
	}
	ptr = nullptr;
}

void EventQueue::register_keyboard() {
	al_register_event_source(ptr, al_get_keyboard_event_source());
}
void EventQueue::register_mouse() {
	al_register_event_source(ptr, al_get_mouse_event_source());
}
