#ifndef SRC_APPCONTEXT_H_
#define SRC_APPCONTEXT_H_

#include "audioSample.h"
#include <memory>
#include "basic_allegro.h"
#include "timer.h"

class AppContext {
public:
	bool initialize();
	void flushEventQueue();
	void startFrameRateUpdates();
	void stopFrameRateUpdates();
	void stopApp();

	bool getRunningFlag() const;
	ALLEGRO_FONT* getMainFont() const;
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
	Display display;
	Font font;
	Queue queue;
	std::unique_ptr<Timer> timer;
	std::unique_ptr<AudioSample> errorSample;
};

bool app_init_alllegro_modules();

#endif /* SRC_APPCONTEXT_H_ */
