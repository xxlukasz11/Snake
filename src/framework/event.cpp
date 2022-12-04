#include "event.h"
#include "timer.h"
#include <unordered_map>

namespace framework {

// @formatter:off
static const std::unordered_map<DisplayEvent, ALLEGRO_EVENT_TYPE> displayEventMapping{
		{ DisplayEvent::CLOSE, ALLEGRO_EVENT_DISPLAY_CLOSE }
};

static const std::unordered_map<int, KeyboardKey> keyboardMapping{
		{ ALLEGRO_KEY_DOWN, KeyboardKey::KEY_DOWN },
		{ ALLEGRO_KEY_UP, KeyboardKey::KEY_UP },
		{ ALLEGRO_KEY_LEFT, KeyboardKey::KEY_LEFT },
		{ ALLEGRO_KEY_RIGHT, KeyboardKey::KEY_RIGHT },
		{ ALLEGRO_KEY_ESCAPE, KeyboardKey::KEY_ESCAPE },
		{ ALLEGRO_KEY_Y, KeyboardKey::KEY_Y },
		{ ALLEGRO_KEY_N, KeyboardKey::KEY_N }
};
// @formatter:on

Event::Event(const ALLEGRO_EVENT& event) :
		event(event) {
}

bool Event::isDisplayEvent(DisplayEvent displayEvent) const {
	return event.type == displayEventMapping.find(displayEvent)->second;
}

bool Event::isEventSource(const Timer& timer) const {
	return event.timer.source == timer.allegroTimer.get();
}

bool Event::isTimerEvent() const {
	return event.type == ALLEGRO_EVENT_TIMER;
}

bool Event::isKeyReleased(KeyboardKey key) const {
	return isKeyReleased() && isKeyCodeMatching(key);
}

bool Event::isKeyPressed(KeyboardKey key) const {
	return isKeyPressed() && isKeyCodeMatching(key);
}

bool Event::isKeyReleased() const {
	return event.type == ALLEGRO_EVENT_KEY_UP;
}

bool Event::isKeyPressed() const {
	return event.type == ALLEGRO_EVENT_KEY_DOWN;
}

const framework::KeyboardKey Event::readKeyFromEvent() const {
	auto key = keyboardMapping.find(event.keyboard.keycode);
	if (key == keyboardMapping.end()) {
		return KeyboardKey::UNKNOWN;
	}
	return key->second;
}

bool Event::isKeyCodeMatching(KeyboardKey key) const {
	return key == readKeyFromEvent();
}

KeyboardKey Event::getKey() const {
	return readKeyFromEvent();
}

} // namespace framework
