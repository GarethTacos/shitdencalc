/* SPDX-License-Identifier: GPL-3.0-or-later */
/*
 * audio.c — shitdencalc
 * Copyright (c) 2025 GarethTacos
 */
#define DR_FLAC_IMPLEMENTATION
#include "dr_flac.h"
#include <AL/al.h>
#include <AL/alc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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

// Load a FLAC and start playback (does not block)
int shitaudio_play_flac(shitaudio *a, const char *filename) {
    if (!a || !filename) return -1;

    // Decode FLAC as 16-bit PCM
    unsigned int channels;
    unsigned int sampleRate;
    drflac_uint64 totalPCMFrameCount;
    drflac_int16 *pcm_data = drflac_open_file_and_read_pcm_frames_s16(
        filename, &channels, &sampleRate, &totalPCMFrameCount, NULL);

    if (!pcm_data) {
        fprintf(stderr, "Failed to load FLAC file: %s\n", filename);
        return -1;
    }

    // Create buffer
    alGenBuffers(1, &a->buffer);
    ALenum err = alGetError();
    if (err != AL_NO_ERROR) {
        fprintf(stderr, "alGenBuffers error: 0x%X\n", err);
        drflac_free(pcm_data, NULL);
        return -1;
    }

    ALenum format = (channels == 1) ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;
    ALsizei size = (ALsizei)(totalPCMFrameCount * channels * sizeof(drflac_int16));
    alBufferData(a->buffer, format, pcm_data, size, sampleRate);
    if ((err = alGetError()) != AL_NO_ERROR) {
        fprintf(stderr, "alBufferData error: 0x%X\n", err);
        alDeleteBuffers(1, &a->buffer);
        a->buffer = 0;
        drflac_free(pcm_data, NULL);
        return -1;
    }

    drflac_free(pcm_data, NULL);
    pcm_data = NULL;

    // Create source and attach buffer
    alGenSources(1, &a->source);
    if ((err = alGetError()) != AL_NO_ERROR) {
        fprintf(stderr, "alGenSources error: 0x%X\n", err);
        alDeleteBuffers(1, &a->buffer);
        a->buffer = 0;
        return -1;
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
// wait until source stops playing
void shitaudio_wait_uf(shitaudio *a) {
    ALint state = 0;
    do {
        alGetSourcei(a->source, AL_SOURCE_STATE, &state);
        usleep(100 * 1000);  // sleep 100ms
    } while (state == AL_PLAYING);
}

