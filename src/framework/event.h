#ifndef SRC_FRAMEWORK_EVENT_H_
#define SRC_FRAMEWORK_EVENT_H_

#include <allegro5/allegro.h>

namespace framework {

enum class KeyboardKey {
	KEY_UP, KEY_LEFT, KEY_RIGHT, KEY_DOWN, KEY_ESCAPE, KEY_Y, KEY_N
};

enum class DisplayEvent {
	CLOSE
};

class Timer;

class Event {
public:
	Event(const ALLEGRO_EVENT& event);
	bool isDisplayEvent(DisplayEvent displayEvent) const;
	bool isEventSource(const Timer& timer) const;
	bool isTimerEvent() const;
	bool isKeyReleased(KeyboardKey key) const;
	bool isKeyPressed(KeyboardKey key) const;
	bool isKeyReleased() const;
	bool isKeyPressed() const;
	KeyboardKey getKey() const;

private:
	bool isKeyCodeMatching(KeyboardKey key) const;
	const framework::KeyboardKey readKeyFromEvent() const;

	ALLEGRO_EVENT event;
};

} // namespace framework

#endif /* SRC_FRAMEWORK_EVENT_H_ */
