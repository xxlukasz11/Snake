#include "../framework/audioSample.h"

AudioSample::AudioSample() :
		sample(nullptr, destroySample) {
}

AudioSample::AudioSample(AllegroAudioSamplePtr sample) :
		sample(std::move(sample)) {
}

void AudioSample::play() const {
	al_play_sample(sample.get(), 1.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
}

void AudioSample::destroySample(ALLEGRO_SAMPLE* sample) {
	al_destroy_sample(sample);
}

std::unique_ptr<AudioSample> AudioSample::loadFromFile(const char* filePath) {
	AllegroAudioSamplePtr samplePtr(al_load_sample(filePath), destroySample);
	if (!samplePtr) {
		return nullptr;
	}
	return std::unique_ptr<AudioSample>(new AudioSample(std::move(samplePtr)));
}
