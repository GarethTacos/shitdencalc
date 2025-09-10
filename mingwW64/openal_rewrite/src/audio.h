/* SPDX-License-Identifier: GPL-3.0-or-later */
/*
 * audio.h — shitdencalc
 * Copyright (c) 2025 GarethTacos
 */
#ifndef AUDIO_H
#define AUDIO_H
#define AL_ALEXT_PROTOTYPES
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/efx.h>
typedef struct shitaudio {
    ALCdevice *device;
    ALCcontext *context;
    ALuint source;
    ALuint buffer;
    ALuint fxslot;
    ALuint fx;
    float duration;
} shitaudio;
int shitaudio_init(shitaudio *a);
//int shitaudio_play_flac(shitaudio *a, const char *filename); deprecated
int shitaudio_opus_genpcm(shitaudio *a, const char *filename);
void shitaudio_play_pcm(shitaudio *a);
void shitaudio_destroy(shitaudio *a);
//void shitaudio_wait_uf(shitaudio *a); deprecated
void shitaudio_stop(shitaudio *a);
void shitaudio_seek(shitaudio *a, float pos_off);
void shitaudio_cheap_replay(shitaudio *a);
void shitaudio_gensource(shitaudio *a);
void shitaudio_pause(shitaudio *a);
void shitaudio_reverb(shitaudio *a);
void shitaudio_fxdie(shitaudio *a);
#endif

