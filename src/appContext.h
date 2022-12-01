#ifndef SRC_APPCONTEXT_H_
#define SRC_APPCONTEXT_H_

#include <memory>
#include "framework/audioSample.h"
#include "framework/timer.h"
#include "framework/display.h"
#include "framework/eventQueue.h"
#include "framework/font.h"
#include "framework/textWriter.h"
#include "framework/event.h"

class AppContext {
public:
	bool initialize();
	void stopApp();

	bool shouldBeRunning() const;
	const framework::Display& getDisplay() const;
	const framework::AudioSample& getErrorAudioSample() const;
	framework::TextWriter& getTextWriter() const;
	framework::Event waitForEvent();
	void startFrameRateUpdates();

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
	std::unique_ptr<framework::Timer> frameRateTimer;
	std::unique_ptr<framework::AudioSample> errorSample;
	std::unique_ptr<framework::TextWriter> textWriter;
};

#endif /* SRC_APPCONTEXT_H_ */
