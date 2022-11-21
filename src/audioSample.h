#ifndef SRC_AUDIOSAMPLE_H_
#define SRC_AUDIOSAMPLE_H_

#include <allegro5/allegro_audio.h>
#include <memory>

class AudioSample {
public:
	AudioSample();
	void play() const;
	static std::unique_ptr<AudioSample> loadFromFile(const char* filePath);

private:
	using AllegroSampleDeleter = void(*)(ALLEGRO_SAMPLE*);

	AudioSample(std::unique_ptr<ALLEGRO_SAMPLE, AllegroSampleDeleter> sample);
	static void destroySample(ALLEGRO_SAMPLE* sample);

	std::unique_ptr<ALLEGRO_SAMPLE, AllegroSampleDeleter> sample;
};

#endif /* SRC_AUDIOSAMPLE_H_ */
