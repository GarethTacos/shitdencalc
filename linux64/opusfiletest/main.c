#include <stdio.h>
#include "opusfile.h"

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
	int channels = head->channel_count;
	printf("Sample rate: %d Channels: %d\n", sample_rate,channels);
	op_free(bgm);
	return 0;
}
