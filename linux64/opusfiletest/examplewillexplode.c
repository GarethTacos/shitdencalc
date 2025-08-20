#include <stdio.h>
#include <stdlib.h>
#include <AL/al.h>
#include <AL/alc.h>
#include <opusfile.h>

#define BUFFER_SIZE 4096  // PCM samples per read

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: %s <file.opus>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
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

    int channels = head->channel_count;
    int sample_rate = 48000;  // Opus standard sample rate

    // Initialize OpenAL
    ALCdevice *device = alcOpenDevice(NULL);
    if (!device) {
        fprintf(stderr, "Failed to open OpenAL device\n");
        op_free(of);
        return 1;
    }

    ALCcontext *context = alcCreateContext(device, NULL);
    alcMakeContextCurrent(context);

    // Generate OpenAL buffer and source
    ALuint buffer, source;
    alGenBuffers(1, &buffer);
    alGenSources(1, &source);

    // Buffer for decoded PCM data (16-bit signed samples)
    short pcm_buffer[BUFFER_SIZE * channels];

    // Read decoded samples from opus file into pcm_buffer
    // We'll read the entire file at once to keep example simple
    int total_samples = 0;
    int capacity = BUFFER_SIZE * 100;  // arbitrary large buffer for example
    short *all_samples = malloc(sizeof(short) * capacity * channels);
    if (!all_samples) {
        fprintf(stderr, "Failed to allocate memory\n");
        op_free(of);
        alcDestroyContext(context);
        alcCloseDevice(device);
        return 1;
    }

    int samples_read;
    while ((samples_read = op_read_stereo(of, pcm_buffer, BUFFER_SIZE)) > 0) {
        if (total_samples + samples_read > capacity) {
            capacity *= 2;
            short *tmp = realloc(all_samples, sizeof(short) * capacity * channels);
            if (!tmp) {
                fprintf(stderr, "Failed to realloc memory\n");
                free(all_samples);
                op_free(of);
                alcDestroyContext(context);
                alcCloseDevice(device);
                return 1;
            }
            all_samples = tmp;
        }
        // Copy decoded samples to all_samples
        for (int i = 0; i < samples_read * channels; i++) {
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
        alcDestroyContext(context);
        alcCloseDevice(device);
        return 1;
    }

    // Buffer audio data into OpenAL buffer
    alBufferData(buffer, format, all_samples, total_samples * channels * sizeof(short), sample_rate);

    free(all_samples);

    // Attach buffer to source and play
    alSourcei(source, AL_BUFFER, buffer);
    alSourcePlay(source);

    // Wait until playback finishes
    //ALint state;
    //do {
    //    alGetSourcei(source, AL_SOURCE_STATE, &state);
    //} while (state == AL_PLAYING);
    getchar();
    // Cleanup OpenAL
    alDeleteSources(1, &source);
    alDeleteBuffers(1, &buffer);
    alcMakeContextCurrent(NULL);
    alcDestroyContext(context);
    alcCloseDevice(device);

    return 0;
}

