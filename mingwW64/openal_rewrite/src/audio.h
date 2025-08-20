/* SPDX-License-Identifier: GPL-3.0-or-later */
/*
 * audio.h — shitdencalc
 * Copyright (c) 2025 GarethTacos
 */
#ifndef AUDIO_H
#define AUDIO_H

#include <AL/al.h>
#include <AL/alc.h>

typedef struct shitaudio {
    ALCdevice *device;
    ALCcontext *context;
    ALuint source;
    ALuint buffer;
} shitaudio;

int shitaudio_init(shitaudio *a);
int shitaudio_play_flac(shitaudio *a, const char *filename);
void shitaudio_destroy(shitaudio *a);
void shitaudio_wait_uf(shitaudio *a);
void shitaudio_stop(shitaudio *a);
#endif

