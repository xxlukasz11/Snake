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
	const Font& getMainFont() const;
	const Display& getDisplay() const;
	const AudioSample& getErrorAudioSample() const;
	Timer& getSnakeMovementTimer() const;
	void waitForEvent(ALLEGRO_EVENT& event);

private:
	bool initDisplay();
	bool loadMainFont();
	bool initFrameRateTimer();
	bool loadAudioSamples();
	void registerEventSources();

	bool runningFlag{ true };
	EventQueue queue;
	std::unique_ptr<Font> font;
	std::unique_ptr<Display> display;
	std::unique_ptr<Timer> snakeMovementTimer;
	std::unique_ptr<AudioSample> errorSample;
};

bool app_init_alllegro_modules();

#endif /* SRC_APPCONTEXT_H_ */
