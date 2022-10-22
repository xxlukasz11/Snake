#ifndef SRC_AUDIOSAMPLE_H_
#define SRC_AUDIOSAMPLE_H_

#include <allegro5/allegro_audio.h>
#include <memory>

class AudioSample {
public:
	AudioSample(ALLEGRO_SAMPLE* sample);
	void play() const;

private:
	using SampleDeleter = void(*)(ALLEGRO_SAMPLE*);
	static void destroySample(ALLEGRO_SAMPLE* sample);

	std::unique_ptr<ALLEGRO_SAMPLE, SampleDeleter> sample;
};

#endif /* SRC_AUDIOSAMPLE_H_ */
