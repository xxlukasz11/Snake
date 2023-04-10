#ifndef SRC_APPCONTEXT_H_
#define SRC_APPCONTEXT_H_

#include <memory>
#include "allegro-cpp/audioSample.h"
#include "allegro-cpp/timer.h"
#include "allegro-cpp/display.h"
#include "allegro-cpp/eventQueue.h"
#include "allegro-cpp/font.h"
#include "allegro-cpp/textWriter.h"
#include "allegro-cpp/event.h"

class AppContext {
public:
	bool initialize();
	void stopApp();

	bool shouldBeRunning() const;
	const allegrocpp::Display& getDisplay() const;
	const allegrocpp::AudioSample& getErrorAudioSample() const;
	allegrocpp::TextWriter& getTextWriter() const;
	allegrocpp::Event waitForEvent();
	void startFrameRateUpdates();

private:
	bool initDisplay();
	bool loadMainFont();
	bool initFrameRateTimer();
	bool loadAudioSamples();
	void registerEventSources();

	bool runningFlag{ true };
	allegrocpp::EventQueue queue;
	std::unique_ptr<allegrocpp::Font> font;
	std::unique_ptr<allegrocpp::Display> display;
	std::unique_ptr<allegrocpp::Timer> frameRateTimer;
	std::unique_ptr<allegrocpp::AudioSample> errorSample;
	std::unique_ptr<allegrocpp::TextWriter> textWriter;
};

#endif /* SRC_APPCONTEXT_H_ */
