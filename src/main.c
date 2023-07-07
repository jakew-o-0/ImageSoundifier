#include "parse_bitmap/parse_bmp.h"
#include <portaudio.h>
#include <stdlib.h>
#include <stdio.h>
#include "utils.h"





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
	for(int i=0; i < TABLE_SIZE; i++) {
		data.wavetable[i] = 0;
	}

	// parse bitmap
	char* path = "/home/jake/code/image_soundifier/resorces/test_image.bmp";
	gen_noise(data.wavetable, TABLE_SIZE, path);
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
	if(Pa_StartStream(stream) != paNoError)
		catch_err(err);

	printf("\n\nplaying sound for 10 secs\n");
	Pa_Sleep(10 * 1000);

	if(Pa_StopStream(stream) != paNoError)
		catch_err(err);

	if(Pa_CloseStream(stream) != paNoError)
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
