#ifndef SRC_APP_HPP_
#define SRC_APP_HPP_

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include "basic_allegro.hpp"

class App {
public:
	bool initDisplay();
	bool loadMainFont();
	bool initFrameRateTimer();
	void registerEventSources();
	void flushEventQueue();

	ALLEGRO_FONT* getMainFont() const;
	float getFrameRateIntervalSeconds() const;
	const Display& getDisplay() const;
	const Timer& getFrameRateTimer() const;
	void waitForEvent(ALLEGRO_EVENT &event);

private:
	Display display;
	Font font;
	Queue queue;
	ALLEGRO_MONITOR_INFO monitor;
	Timer timer;
	float dt{ 0.06f };
};

bool init_alllegro_modules();


#endif /* SRC_APP_HPP_ */
