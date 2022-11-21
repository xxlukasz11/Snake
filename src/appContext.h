#ifndef SRC_APPCONTEXT_H_
#define SRC_APPCONTEXT_H_

#include <memory>
#include "audioSample.h"
#include "timer.h"
#include "display.h"
#include "eventQueue.h"
#include "font.h"

class AppContext {
public:
	bool initialize();
	void flushEventQueue();
	void startFrameRateUpdates();
	void stopFrameRateUpdates();
	void stopApp();

	bool getRunningFlag() const;
	const Font& getMainFont() const;
	float getFrameRateIntervalSeconds() const;
	const Display& getDisplay() const;
	const AudioSample& getErrorAudioSample() const;
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
	std::unique_ptr<Timer> timer;
	std::unique_ptr<AudioSample> errorSample;
};

bool app_init_alllegro_modules();

#endif /* SRC_APPCONTEXT_H_ */
