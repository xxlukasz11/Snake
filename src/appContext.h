#ifndef SRC_APPCONTEXT_H_
#define SRC_APPCONTEXT_H_

#include <memory>
#include "framework/audioSample.h"
#include "framework/timer.h"
#include "framework/display.h"
#include "framework/eventQueue.h"
#include "framework/font.h"

class AppContext {
public:
	bool initialize();
	void stopApp();

	bool getRunningFlag() const;
	const framework::Font& getMainFont() const;
	const framework::Display& getDisplay() const;
	const framework::AudioSample& getErrorAudioSample() const;
	framework::Timer& getSnakeMovementTimer() const;
	void waitForEvent(ALLEGRO_EVENT& event);

private:
	bool initDisplay();
	bool loadMainFont();
	bool initFrameRateTimer();
	bool loadAudioSamples();
	void registerEventSources();

	bool runningFlag{ true };
	framework::EventQueue queue;
	std::unique_ptr<framework::Font> font;
	std::unique_ptr<framework::Display> display;
	std::unique_ptr<framework::Timer> snakeMovementTimer;
	std::unique_ptr<framework::AudioSample> errorSample;
};

bool app_init_alllegro_modules();

#endif /* SRC_APPCONTEXT_H_ */
