#ifndef SRC_AUDIOSAMPLE_H_
#define SRC_AUDIOSAMPLE_H_

#include <allegro5/allegro_audio.h>
#include <memory>

namespace framework {

class AudioSample {
public:
	AudioSample();
	void play() const;
	static std::unique_ptr<AudioSample> loadFromFile(const char* filePath);

private:
	using AllegroSampleDeleter = void(*)(ALLEGRO_SAMPLE*);
	using AllegroAudioSamplePtr = std::unique_ptr<ALLEGRO_SAMPLE, AllegroSampleDeleter>;

	AudioSample(AllegroAudioSamplePtr sample);
	static void destroySample(ALLEGRO_SAMPLE* sample);

	AllegroAudioSamplePtr sample;
};

} // namespace framework

#endif /* SRC_AUDIOSAMPLE_H_ */
