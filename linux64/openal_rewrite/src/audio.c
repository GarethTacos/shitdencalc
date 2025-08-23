/* SPDX-License-Identifier: GPL-3.0-or-later */
/*
 * audio.c — shitdencalc
 * Copyright (c) 2025 GarethTacos
 */
//#define DR_FLAC_IMPLEMENTATION
//#include "dr_flac.h"
#include <AL/al.h>
#include <AL/alc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <opusfile.h>

typedef struct shitaudio {
    ALCdevice *device;
    ALCcontext *context;
    ALuint source;
    ALuint buffer;
} shitaudio;

// Initialize OpenAL context and zero state
int shitaudio_init(shitaudio *a) {
    if (!a) return -1;
    memset(a, 0, sizeof *a);

    a->device = alcOpenDevice(NULL);
    if (!a->device) {
        fprintf(stderr, "Failed to open OpenAL device\n");
        return -1;
    }

    a->context = alcCreateContext(a->device, NULL);
    if (!a->context) {
        fprintf(stderr, "Failed to create OpenAL context\n");
        alcCloseDevice(a->device);
        a->device = NULL;
        return -1;
    }

    if (!alcMakeContextCurrent(a->context)) {
        fprintf(stderr, "Failed to make OpenAL context current\n");
        alcDestroyContext(a->context);
        alcCloseDevice(a->device);
        a->context = NULL;
        a->device = NULL;
        return -1;
    }

    return 0;
}

// destroys the context and device
void shitaudio_destroy(shitaudio *a) {
    if (!a) return;

    if (a->context) {
        alcMakeContextCurrent(NULL);
        alcDestroyContext(a->context);
        a->context = NULL;
    }

    if (a->device) {
        alcCloseDevice(a->device);
        a->device = NULL;
    }
}
// just stops music and clears buffer
void shitaudio_stop(shitaudio *a){
    if (!a) return;

    if (a->source) {
        alSourceStop(a->source);
        alDeleteSources(1, &a->source);
        a->source = 0;
    }

    if (a->buffer) {
        alDeleteBuffers(1, &a->buffer);
        a->buffer = 0;
    }
}
// Load Opus Ogg audio as pcm and shove into buffer
int shitaudio_opus_genpcm(shitaudio *a, const char *filename){
	if (!a || !filename) return -1;
	// clear buffer and source so no weird shit piped in
	// initially only wanted to clear buffer but since buffer is base of source need to clear source first then buffer so weird thing don't happen.
	shitaudio_stop(a);
       int err;
	OggOpusFile *bgm = op_open_file(filename, &err);
	if (bgm == NULL) {
		fprintf(stderr, "Failed to open Opus file (error code: %d)\n", err);
		return 1;
	}
	const OpusHead *head = op_head(bgm, -1); // -1 for first logical bitstream
	const int sample_rate = 48000; // Opus always 48 kHz
	opus_int64 total_samples = op_pcm_total(bgm,-1); // total no. of sampels
	int channels = head->channel_count;
	// for debug
	//printf("Sample rate: %d Channels: %d\n", sample_rate,channels);
	//printf("Seekable: %d\n", op_seekable(bgm));
	//printf("Bitrate: %d\n",op_bitrate(bgm,-1));
	//printf("Sample num: %d \n", total_samples);

	opus_int16* pcm_data = malloc(op_pcm_total(bgm,-1) * 2 * sizeof(opus_int16));	// fat buffer so can read fat opus
	opus_int64 samples_read_total = 0; 
	while (samples_read_total < total_samples) { 
		// reads something and has to skip two at a time because stereo is Ln Rn
		int samples_read = op_read_stereo(bgm, pcm_data + samples_read_total * 2, total_samples - samples_read_total); 
		if (samples_read <= 0) break; 
		// EOF or error 
		samples_read_total += samples_read; 
	}
	// make a buffer
	alGenBuffers(1, &a->buffer);
	ALenum alerr = alGetError();
	if (alerr != AL_NO_ERROR) {
		fprintf(stderr, "alGenBuffers error: 0x%X\n", alerr);
		free(pcm_data);
		return -1;
	}
	
	// generate format
	ALenum format = (channels == 1) ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;
	// find size from total_samples * channels (2 in most cases) and size of opus_int16
	ALsizei size = total_samples * channels * sizeof(opus_int16);
	alBufferData(a->buffer,format,pcm_data,size,sample_rate);
	if ((err = alGetError()) != AL_NO_ERROR) {
		fprintf(stderr, "alBufferData error: 0x%X\n", alerr);
		alDeleteBuffers(1, &a->buffer);
		a->buffer = 0;
		free(pcm_data);
		return -1;
	}
	// free so no die also because we no longer require the data
	free(pcm_data);
	op_free(bgm);
	return 0;
}
void shitaudio_play_pcm(shitaudio *a){
    if (!a) return;
// clear source so no weird behaviour
// gen alerr
ALenum err = alGetError();
    if (a->source) {
        alSourceStop(a->source);
        alDeleteSources(1, &a->source);
        a->source = 0;
    }
    alGenSources(1, &a->source);
    if ((err = alGetError()) != AL_NO_ERROR) {
        fprintf(stderr, "alGenSources error: 0x%X\n", err);
        alDeleteBuffers(1, &a->buffer);
        a->buffer = 0;
        return;
    }

    alSourcei(a->source, AL_BUFFER, a->buffer);
    alSourcePlay(a->source);
    if ((err = alGetError()) != AL_NO_ERROR) {
        fprintf(stderr, "alSourcePlay error: 0x%X\n", err);
        // cleanup partial
        alDeleteSources(1, &a->source);
        a->source = 0;
        alDeleteBuffers(1, &a->buffer);
        a->buffer = 0;
        return;
    }
}
