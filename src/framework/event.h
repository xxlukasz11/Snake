#ifndef SRC_FRAMEWORK_EVENT_H_
#define SRC_FRAMEWORK_EVENT_H_

#include <allegro5/allegro.h>

namespace framework {

enum class KeyboardKey {
	KEY_UP, KEY_LEFT, KEY_RIGHT, KEY_DOWN, KEY_ESCAPE, KEY_Y, KEY_N, UNKNOWN
};

enum class EventType {
	DISPLAY_CLOSE, TIMER_EXPIRED, KEY_PRESSED, KEY_RELEASED, UNKNOWN
};

class Timer;

class Event {
public:
	Event(const ALLEGRO_EVENT& event);
	EventType getEventType() const;
	KeyboardKey getKey() const;

	bool isEventSource(const Timer& timer) const;
	bool isKeyReleased(KeyboardKey key) const;
	bool isKeyPressed(KeyboardKey key) const;

private:
	bool isKeyReleased() const;
	bool isKeyPressed() const;
	KeyboardKey readKeyFromEvent() const;
	EventType readEventType() const;

	ALLEGRO_EVENT event;
};

} // namespace framework

#endif /* SRC_FRAMEWORK_EVENT_H_ */
