#ifndef SRC_APPCONTEXT_H_
#define SRC_APPCONTEXT_H_

#include "basic_allegro.hpp"

class AppContext {
public:
	bool initialize();
	void flushEventQueue();
	void startFrameRateUpdates();
	void stopFrameRateUpdates();

	ALLEGRO_FONT* getMainFont() const;
	float getFrameRateIntervalSeconds() const;
	const Display& getDisplay() const;
	void waitForEvent(ALLEGRO_EVENT& event);

private:
	bool initDisplay();
	bool loadMainFont();
	bool initFrameRateTimer();
	void registerEventSources();

	Display display;
	Font font;
	Queue queue;
	Timer timer;
};

bool init_alllegro_modules();


#endif /* SRC_APPCONTEXT_H_ */
