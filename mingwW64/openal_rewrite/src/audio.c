/* SPDX-License-Identifier: GPL-3.0-or-later */
/*
 * audio.c — shitdencalc
 * Copyright (c) 2025 GarethTacos
 */
//#define DR_FLAC_IMPLEMENTATION
//#include "dr_flac.h"
// NOTES!!!
// probably need to make this more fault tolerant
// BOILERPLATE TIIIMMEEEE!!!
// But like fault tolerant to a specfic degree
// not noob tolerant (although i am a noob so idk actually)
// just tolerant to my own stupidity or smth
// important shit so must not forget to define
#define AL_ALEXT_PROTOTYPES
#include "audio.h"
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/efx.h>
#include <stdio.h>
#include <stdlib.h>
#include <opusfile.h>
#include <string.h>

// HAHAHAHAHA EPHEX BABEEEEEEE
// ok i should sotp
// apparently don't need double-def
// refer to header

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
// stops music only
void shitaudio_pause(shitaudio *a){
	if (!a) return;
	if (a->source) alSourceStop(a->source);
	return;
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

	opus_int16* pcm_data = malloc(total_samples * 2 * sizeof(opus_int16));	// fat buffer so can read fat opus
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
	// have to find out the diff between this and the nested one
	ALenum alerr = alGetError();
	if ((alerr = alGetError()) != AL_NO_ERROR) {
		fprintf(stderr, "alGenBuffers error: 0x%X\n", alerr);
		free(pcm_data);
		return -1;
	}
	
	// generate format
	// ALenum format = (channels == 1) ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;
	ALenum format = AL_FORMAT_STEREO16;
	// find size from total_samples * channels (2 in most cases) and size of opus_int16
	ALsizei size = total_samples * channels * sizeof(opus_int16);
	alBufferData(a->buffer,format,pcm_data,size,sample_rate);
	if ((alerr = alGetError()) != AL_NO_ERROR) {
		fprintf(stderr, "alBufferData error: 0x%X\n", alerr);
		alDeleteBuffers(1, &a->buffer);
		a->buffer = 0;
		free(pcm_data);
		return -1;
	}
	a->duration = (float)total_samples / (float)sample_rate;
	// free so no die also because we no longer require the data
	free(pcm_data);
	op_free(bgm);
	return 0;
}
//seek fn
void shitaudio_seek(shitaudio *a, float pos_off){
	if (!a || !pos_off || !a->source || !a->buffer) return;
	//ALfloat pos = 0.0f;
	//alGetSourcef(a->source, AL_SEC_OFFSET, &pos);
	// change duration
	if (pos_off < 0.0f) pos_off = 0.0f;
	if (pos_off > a->duration) pos_off = a->duration;
	alSourceStop(a->source);
	alSourcef(a->source, AL_SEC_OFFSET,pos_off);
	alSourcePlay(a->source);
	return;
}
// seeks to 0.0 and plays source
void shitaudio_cheap_replay(shitaudio *a){
	ALenum alerr = alGetError();
	// resets source, keeps data
	alSourceStop(a->source);
	alSourcef(a->source,AL_SEC_OFFSET,0.0f);
	alSourcePlay(a->source);
	
	if ((alerr = alGetError()) != AL_NO_ERROR) {
		fprintf(stderr, "alSourcePlay error: 0x%X\n", alerr);
		// cleanup partial
		alDeleteSources(1, &a->source);
		a->source = 0;
		alDeleteBuffers(1, &a->buffer);
		a->buffer = 0;
		return;
	}

	return;
}
// gen source only
void shitaudio_gensource(shitaudio *a){
	ALenum alerr = alGetError();
	if (!a) return;
	// make a new source
	if (a->source) {
		alSourceStop(a->source);
		alDeleteSources(1, &a->source);
		a->source = 0;
	}
	alGenSources(1, &a->source);
	if ((alerr = alGetError()) != AL_NO_ERROR) {
        	fprintf(stderr, "alGenSources error: 0x%X\n", alerr);
        	alDeleteBuffers(1, &a->buffer);
        	a->buffer = 0;
        	return;
    }
	// attach buffer to source
    alSourcei(a->source, AL_BUFFER, a->buffer);
}
// gen source and play
void shitaudio_play_pcm(shitaudio *a){
    if (!a) return;
// clear source so no weird behaviour
// gen alerr
ALenum alerr = alGetError();
    if (a->source) {
        alSourceStop(a->source);
        alDeleteSources(1, &a->source);
        a->source = 0;
    }
    alGenSources(1, &a->source);
    if ((alerr = alGetError()) != AL_NO_ERROR) {
        fprintf(stderr, "alGenSources error: 0x%X\n", alerr);
        alDeleteBuffers(1, &a->buffer);
        a->buffer = 0;
        return;
    }

    alSourcei(a->source, AL_BUFFER, a->buffer);
    alSourcePlay(a->source);
    if ((alerr = alGetError()) != AL_NO_ERROR) {
        fprintf(stderr, "alSourcePlay error: 0x%X\n", alerr);
        // cleanup partial
        alDeleteSources(1, &a->source);
        a->source = 0;
        alDeleteBuffers(1, &a->buffer);
        a->buffer = 0;
        return;
    }
}

// I like em spicy mhehehe
void shitaudio_reverb(shitaudio *a){
	if (!a || !a->device) return;
	ALboolean efxSupported = alcIsExtensionPresent(a->device, "ALC_EXT_EFX");
	if (!efxSupported) {
		// die
		return;
	}
	alGenAuxiliaryEffectSlots(1, &a->fxslot);
	alGenEffects(1, &a->fx);
	// Set fx type to R E V E R B
	alEffecti(a->fx, AL_EFFECT_TYPE, AL_EFFECT_REVERB);
	// params and boring stuff *insert yawn*
	alEffectf(a->fx, AL_REVERB_DECAY_TIME, 2.0f);        // 2 seconds decay
	alEffectf(a->fx, AL_REVERB_DENSITY, 0.8f);          // Room density
	alEffectf(a->fx, AL_REVERB_DIFFUSION, 0.9f);        // Sound diffusion
	alEffectf(a->fx, AL_REVERB_GAIN, 0.7f);             // Overall volume
	alEffectf(a->fx, AL_REVERB_GAINHF, 0.5f);           // High frequency attenuation
	// load her up real nice ;)
	alAuxiliaryEffectSloti(a->fxslot, AL_EFFECTSLOT_EFFECT, a->fx);
	// idk this part lol
	// Attach the source to the fx slot
	ALuint send = 0; // usually send index 0
	alSource3i(a->source, AL_AUXILIARY_SEND_FILTER, a->fxslot, send, AL_FILTER_NULL);
}

// DIE POTATO DIEEEE
void shitaudio_fxdie(shitaudio *a){
	// kill you
	if(a->fx) { 
		alDeleteEffects(1, &a->fx);
		a->fx = 0;
	}
	// aaaand kill you :3
	if (a->fxslot) {
		alDeleteAuxiliaryEffectSlots(1, &a->fxslot);
		a->fxslot = 0;
	}
}
