#include "parse_bmp.h"
#include <portaudio.h>
#include <stdlib.h>
#include <stdio.h>


typedef struct {
	float wavetable[256];
	int left_phase;
	int right_phase;
} paData;


void catch_err(PaError err);





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






int main(void) {
	float wave_table[256];
	for(int i=0; i < 256; i++) {
		wave_table[i] = 0;
	}

	char* path = "/home/jake/image_soundifier/resorces/test_image.bmp";
	get_header(wave_table, 256, path);



	paData data;
	PaError err;
	PaStream* stream;
	PaStreamParameters output_params;
	
	data.left_phase = data.right_phase = 0;

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
			44100,
			256,
			paClipOff,
			patestCallback,
			&data);

	if(err != paNoError)
		catch_err(err);
	
	err = Pa_StartStream(stream);
	if(err != paNoError)
		catch_err(err);

	printf("sleep for 10 seconds\n");
	Pa_Sleep(10 * 1000);

	err = Pa_StopStream(stream);
	if(err != paNoError)
		catch_err(err);

	err = Pa_CloseStream(stream);
	if(err != paNoError)
		catch_err(err);

	Pa_Terminate();
	printf("Test Finished\n");
	return 0;
}













void catch_err(PaError err) {
	printf("portaudio error: \n%s", Pa_GetErrorText(err));
	exit(1);
}
