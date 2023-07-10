#include "parse_bitmap/parse_bmp.h"
#include <portaudio.h>
#include <stdlib.h>
#include <stdio.h>
#include "utils.h"
#include "pool_library/pool_utils.h"





typedef struct {
	float wavetable[TABLE_SIZE];
	int left_phase;
	int right_phase;
} paData;

void catch_err(PaError err);
void write_to_file(paData* data);
void innit_paudio(PaStream* stream, paData* data);
static int patestCallback( const void *inputBuffer, void *outputBuffer,
                           unsigned long framesPerBuffer,
                           const PaStreamCallbackTimeInfo* timeInfo,
                           PaStreamCallbackFlags statusFlags,
                           void *userData );




int main(void) {
	// init data struct
	paData data;
	data.left_phase = data.right_phase = 0;
	chord_pool* chordPool = malloc(sizeof(chord_pool));

	// parse bitmap
	char* path = "/home/jake/image_soundifier/resorces/test_image.bmp";
	gen_chords(chordPool, path);


	{
	// init portaudio
	PaStream* stream;

	PaError err;
	PaStreamParameters output_params;

	err = Pa_Initialize();
	if(err != paNoError) 
		catch_err(err);

	output_params.device = Pa_GetDefaultOutputDevice();
	if(output_params.device == paNoDevice) 
		exit(1);
	output_params.channelCount = 2;
	output_params.sampleFormat = paFloat32;
	output_params.suggestedLatency = Pa_GetDeviceInfo(output_params.device)->defaultLowOutputLatency;
	output_params.hostApiSpecificStreamInfo = NULL;

	err = Pa_OpenStream(&stream,
			NULL,
			&output_params,
			SAMPLE_RATE,
			TABLE_SIZE,
			paClipOff,
			patestCallback,
			&data);

	if(err != paNoError)
		catch_err(err);


	// play stream
	if((err = Pa_StartStream(stream)) != paNoError)
		catch_err(err);

	printf("\n\n\nplaying chord progression\n\n");
	for(int i = 0; i < chordPool->size; i++){
		for(int j = 0; j < TABLE_SIZE; j++) {
			data.wavetable[j] = chordPool->chord_ptr[chordPool->size].wavetable[j];
		}
		int chord_duration = chordPool->chord_ptr[chordPool->size].chord_pixel.G;
		Pa_Sleep(chord_duration * 100);
	}


	if((err = Pa_StopStream(stream)) != paNoError)
		catch_err(err);

	if((Pa_CloseStream(stream)) != paNoError)
		catch_err(err);

	Pa_Terminate();
	printf("Test Finished\n");
	}


	printf("writing wave to file\n");
	write_to_file(&data);
}



static int patestCallback( const void *inputBuffer, void *outputBuffer,
                           unsigned long framesPerBuffer,
                           const PaStreamCallbackTimeInfo* timeInfo,
                           PaStreamCallbackFlags statusFlags,
                           void *userData ) 
{
	paData* data = (paData*)userData;
	float* out = (float*)outputBuffer;

	(void) timeInfo;
	(void) inputBuffer;
	(void) statusFlags;

	int i;
	for(i = 0; i < framesPerBuffer; i++) {
		*out++ = data->wavetable[data->left_phase];
		*out++ = data->wavetable[data->right_phase];

		data->left_phase += 1;
		if(data->left_phase >= 256)
			data->left_phase -= 256;
		
		data->right_phase += 1;
		if(data->right_phase >= 256)
			data->right_phase -= 256;
	}

	return 0;
}





void innit_paudio(PaStream* stream, paData* data) {
}




void write_to_file(paData* data) {
	FILE *fptr =  fopen("./wavetable", "wb");
	fwrite(data, sizeof(paData), 1, fptr);
}




void catch_err(PaError err) {
	printf("portaudio error: \n%s", Pa_GetErrorText(err));
	exit(1);
}
