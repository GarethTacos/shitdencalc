#define DR_FLAC_IMPLEMENTATION
#include "dr_flac.h"              // FLAC decoder API
#include <cubeb/cubeb.h>          // Cubeb audio API
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>               // sleep()

typedef struct {
    drflac* flac;  // Pointer to FLAC decoder
} playback_data;

// Callback function that Cubeb uses to get audio data
long data_callback(cubeb_stream* stm,
                   void* user_ptr,
                   const void* input_buffer,
                   void* output_buffer,
                   long nframes) 
{
    (void)input_buffer;  // Unused parameter, suppress warning
    (void)stm;           // Unused parameter, suppress warning

    playback_data* pd = (playback_data*)user_ptr;
    drflac_uint64 framesToRead = (drflac_uint64)nframes;
    drflac_int16* out = (drflac_int16*)output_buffer;

    // Read PCM frames from the FLAC decoder
    drflac_uint64 framesRead = drflac_read_pcm_frames_s16(pd->flac, framesToRead, out);

    // If we reached the end of the file, rewind the FLAC decoder
    if (framesRead < framesToRead) {
        // Rewind FLAC decoder to the beginning of the file
        drflac_seek_to_pcm_frame(pd->flac, 0);  // Seek to the beginning (frame 0)
        // Optionally, you can log that we are looping back
        // printf("Looping back to the start!\n");
        framesRead = drflac_read_pcm_frames_s16(pd->flac, framesToRead, out);
    }

    return (long)framesRead;  // Return the number of frames that were actually read
}

// Stream state changes (started, stopped, drained, etc.)
void state_callback(cubeb_stream* stm, void* user_ptr, cubeb_state state) {
    (void)stm; (void)user_ptr; (void)state;
}

// Function to load and play the audio in a loop
void shitbgm(void) {
    const char* filename = "iamu_miku.flac";

    // Open FLAC file for decoding
    drflac* pFlac = drflac_open_file(filename, NULL);
    if (pFlac == NULL) {
        fprintf(stderr, "Failed to open FLAC file: %s\n", filename);
        return;
    }

    // Initialize Cubeb context
    cubeb* ctx;
    if (cubeb_init(&ctx, "dr_flac_cubeb", NULL) != CUBEB_OK) {
        fprintf(stderr, "Failed to initialize Cubeb context\n");
        drflac_close(pFlac);
        return;
    }

    // Configure output stream parameters to match FLAC file
    cubeb_stream_params outParams;
    outParams.format   = CUBEB_SAMPLE_S16NE;
    outParams.rate     = pFlac->sampleRate;
    outParams.channels = pFlac->channels;
    outParams.layout   = CUBEB_LAYOUT_UNDEFINED;
    outParams.prefs    = CUBEB_STREAM_PREF_NONE;

    // Query minimal safe latency
    uint32_t latency;
    cubeb_get_min_latency(ctx, &outParams, &latency);

    // Bundle decoder handle for callback
    playback_data pd = { .flac = pFlac };

    // Create output-only stream
    cubeb_stream* stream;
    if (cubeb_stream_init(ctx, &stream,
                          "dr_flac_playback",    // Stream name
                          NULL, NULL,            // No input
                          NULL, &outParams,      // Only output
                          latency,
                          data_callback,
                          state_callback,
                          &pd) != CUBEB_OK) {
        fprintf(stderr, "Failed to open Cubeb stream\n");
        cubeb_destroy(ctx);
        drflac_close(pFlac);
        return;
    }

    // Start playback
    cubeb_stream_start(stream);

    // Sleep for the duration of the FLAC file. This is just to keep the program alive
    // while audio is playing. You may want to modify this if your loop isn't always
    // based on the duration of a single file.
    double duration = (double)pFlac->totalPCMFrameCount / pFlac->sampleRate;
    sleep((unsigned int)ceil(duration * 65536));

    // Stop and clean up
    cubeb_stream_stop(stream);
    cubeb_stream_destroy(stream);
    cubeb_destroy(ctx);
    drflac_close(pFlac);
}

