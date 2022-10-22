#include "audioSample.h"

AudioSample::AudioSample(ALLEGRO_SAMPLE* sample) :
		sample(sample, destroySample) {
}

void AudioSample::play() const {
	al_play_sample(sample.get(), 1.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
}

void AudioSample::destroySample(ALLEGRO_SAMPLE* sample) {
	al_destroy_sample(sample);
}
