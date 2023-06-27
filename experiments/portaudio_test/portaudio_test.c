#include <math.h>
#include <portaudio.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define S_RATE (44100)

float calc_freq(int key);
float* calc_wav_table(float F, float A, float P);
void catch_err(PaError err);

typedef struct {
	float wavetable[256];
	int left_phase;
	int right_phase;
} paData;





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
	paData data;
	PaError err;
	PaStream* stream;
	PaStreamParameters output_params;
	
	float freq = calc_freq(2);
	float* wav = calc_wav_table(freq, 0.5, 0);
	data.left_phase = data.right_phase = 0;
	for(int i = 0; i < 256; i++){
		data.wavetable[i] = wav[i];
	}

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
						S_RATE,
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







float calc_freq(int key) {
	return 110 * pow(2.0, (1.0/12) * key);
}

float* calc_wav_table(float F, float A, float P) {
	static float table[256];
	
	for(int n = 0; n < 256; n++) {
		table[n] = A * sin((2. * M_PI) * F * (float)n / (float)S_RATE + P);
	}

	return table;
}




void catch_err(PaError err) {
	printf("portaudio error: \n%s", Pa_GetErrorText(err));
	exit(1);
}
