#include "../headers/AudioInterface.hpp"
#include <iostream>
#include <ranges>


AudioInterface::AudioInterface( ImageParser& parser_ ) : parser{parser_}, IsValid{true} {
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
    (void)input;
    (void)timeInfo;
    (void)statusFlags;
    (void)frameCount;

    if( AudioBuff.size() < 2000 ) {
        if( IsValid ) {
            IsValid = parser.GenChord(AudioBuff);
        }
        else if(AudioBuff.empty()){
            EndStream();
        }
    }

    namespace vw = std::ranges::views;
    auto* out = static_cast<float*>(output);
    for(int i : vw::iota(0, TABLE_SIZE)) {
        *(out++) = AudioBuff.front();
        AudioBuff.pop();
    }

    return paContinue;
}


void AudioInterface::PlayStream() {
    err = Pa_StartStream(stream);
    if(err != paNoError)
        CatchErr();
}

void AudioInterface::EndStream() {
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