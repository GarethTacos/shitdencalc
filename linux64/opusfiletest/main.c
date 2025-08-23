#include <stdio.h>
#include <stdlib.h>
#include "opusfile.h"
#include <AL/al.h>
#include <AL/alc.h>
#include <unistd.h>
int main(){
	printf("test\n");
	int err;
	OggOpusFile *bgm = op_open_file("nekobgm.ogg", &err);
	if (bgm == NULL) {
		fprintf(stderr, "Failed to open Opus file (error code: %d)\n", err);
		return 1;
	}
	const OpusHead *head = op_head(bgm, -1); // -1 for first logical bitstream
	const int sample_rate = 48000; // Opus always 48 kHz
	opus_int64 total_samples = op_pcm_total(bgm,-1); // total no. of sampels
	int channels = head->channel_count;
	printf("Sample rate: %d Channels: %d\n", sample_rate,channels);
	printf("Seekable: %d\n", op_seekable(bgm));
	printf("Bitrate: %d\n",op_bitrate(bgm,-1));
	printf("Sample num: %d \n", total_samples);

	opus_int16* pcm_buffer = malloc(op_pcm_total(bgm,-1) * 2 * sizeof(opus_int16));	// fat buffer so can read fat opus
	opus_int64 samples_read_total = 0; 
	while (samples_read_total < total_samples) { 
		// reads something and has to skip two at a time because stereo is Ln Rn
		int samples_read = op_read_stereo(bgm, pcm_buffer + samples_read_total * 2, total_samples - samples_read_total); 
		if (samples_read <= 0) break; 
		// EOF or error 
		samples_read_total += samples_read; 
	}
	// openAL invasion
	// default device
	ALCdevice *device = alcOpenDevice(NULL);
	// make context so can IEE
	ALCcontext *context = alcCreateContext(device,NULL);
	alcMakeContextCurrent(context);
	// make buffer to store poopoo
	ALuint buffer = 0;
	alGenBuffers(1,&buffer);
	// generate format
	ALenum format = (channels == 1) ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;
	// find size from total_samples * channels (2 in most cases) and size of opus_int16
	ALsizei size = total_samples * channels * sizeof(opus_int16);
	alBufferData(buffer,format,pcm_buffer,size,sample_rate);
	// free so no die also because we no longer require the data
	free(pcm_buffer);
	op_free(bgm);
	// make source so can play shit
	ALuint source = 0;
	alGenSources(1, &source);
	// attach buffer to sauce
	alSourcei(source,AL_BUFFER,buffer);
	// finally play the idiot
	alSourcePlay(source);
	// wait until key press
	getchar();
	// kill everything in openal land
	alSourceStop(source);
	alDeleteSources(1,&source);
	alDeleteBuffers(1,&buffer);
	alcMakeContextCurrent(NULL);
	alcDestroyContext(context);
	alcCloseDevice(device);
	source = 0;
	buffer = 0;
	device = 0;
	context = 0;
	return 0;
}
