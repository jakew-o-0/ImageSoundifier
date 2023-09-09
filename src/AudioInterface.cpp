#include "../headers/AudioInterface.hpp"
#include <iostream>
#include <ranges>


AudioInterface::AudioInterface(std::vector<chord>& Table) : WaveTable{Table}, WaveTablePos{0} {
    err =  Pa_Initialize();
    if(err != paNoError) { CatchErr(); }

    err = Pa_OpenDefaultStream(&stream,
                               0,
                               1,
                               paFloat32,
                               SAMPLE_RATE,
                               TABLE_SIZE,
                               PaCallback,
                               this);
    if(err != paNoError) { CatchErr(); }
}


int AudioInterface::Callback(const void *input, void *output, unsigned long frameCount,
                             const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags) {
    auto* out = static_cast<float*>(output);

    for(auto i : WaveTable[WaveTablePos].wavetable) {
        *(out++) = i;
    }
    WaveTablePos++;

    return paContinue;
}


void AudioInterface::PlayStream() {
    err = Pa_StartStream(stream);
    if(err != paNoError)
        CatchErr();

    while (WaveTablePos <= WaveTable.size()) {
        Pa_Sleep(0);
    }

    err = Pa_StopStream(stream);
    if(err != paNoError)
        CatchErr();

    Pa_Terminate();
}


void AudioInterface::CatchErr() const {
    std::cout
        << "PortAudio Error: "
        << Pa_GetErrorText(err)
        << std::endl;
    exit(-1);
}