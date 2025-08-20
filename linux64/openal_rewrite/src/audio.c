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
// wait until source stops playing
void shitaudio_wait_uf(shitaudio *a) {
    if (!a) return;

    ALint state = 0;
    do {
        alGetSourcei(a->source, AL_SOURCE_STATE, &state);
        usleep(100 * 1000);  // sleep 100ms
    } while (state == AL_PLAYING);
}

// Load a FLAC and start playback (does not block)
int shitaudio_play_flac(shitaudio *a, const char *filename) {
	// make sure stuff isn't weirdly piped in
	shitaudio_stop(a);
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
// Load Opus Ogg audio (also does not block)
int shitaudio_play_opus(shitaudio *a, const char *filename){
	shitaudio_stop(a);
    if (!a || !filename) return -1;
int err;
    // Open Opus file
    OggOpusFile *of = op_open_file(filename, &err);
    if (!of) {
        fprintf(stderr, "Failed to open Opus file: %s (error %d)\n", filename, err);
        return 1;
    }

    // Get sample rate and channels from the Opus file
    const OpusHead *head = op_head(of, -1);
    if (!head) {
        fprintf(stderr, "Failed to get Opus file info\n");
        op_free(of);
        return 1;
    }

    unsigned int channels = head->channel_count;
    unsigned int sample_rate = 48000;  // Opus standard sample rate

    // Generate OpenAL buffer and source
    alGenBuffers(1, &a->buffer);
    alGenSources(1, &a->source);

    // Buffer for decoded PCM data (16-bit signed samples)
    short pcm_buffer[4096 * channels];

    // Read decoded samples from opus file into pcm_buffer
    // We'll read the entire file at once to keep example simple
    int total_samples = 0;
    int capacity = 4096 * 100;  // arbitrary large buffer for example
    short *all_samples = malloc(sizeof(short) * capacity * channels);
    if (!all_samples) {
        fprintf(stderr, "Failed to allocate memory\n");
        op_free(of);
        alcDestroyContext(a->context);
        alcCloseDevice(a->device);
        return 1;
    }

    int samples_read;
    while ((samples_read = op_read_stereo(of, pcm_buffer, 4096)) > 0) {
        if (total_samples + samples_read > capacity) {
            capacity *= 2;
            short *tmp = realloc(all_samples, sizeof(short) * capacity * channels);
            if (!tmp) {
                fprintf(stderr, "Failed to realloc memory\n");
                free(all_samples);
                op_free(of);
                alcDestroyContext(a->context);
                alcCloseDevice(a->device);
                return 1;
            }
            all_samples = tmp;
        }
        // Copy decoded samples to all_samples
        for (unsigned int i = 0; i < samples_read * channels; i++) {
            all_samples[total_samples * channels + i] = pcm_buffer[i];
        }
        total_samples += samples_read;
    }

    op_free(of);

    // Determine OpenAL format
    ALenum format;
    if (channels == 1)
        format = AL_FORMAT_MONO16;
    else if (channels == 2)
        format = AL_FORMAT_STEREO16;
    else {
        fprintf(stderr, "Unsupported channel count: %d\n", channels);
        free(all_samples);
        alcDestroyContext(a->context);
        alcCloseDevice(a->device);
        return 1;
    }

    // Buffer audio data into OpenAL buffer
    alBufferData(a->buffer, format, all_samples, total_samples * channels * sizeof(short), sample_rate);
    free(all_samples);

    // Attach buffer to source and play
    alSourcei(a->source, AL_BUFFER, a->buffer);
    alSourcePlay(a->source);
    return 0;
}
