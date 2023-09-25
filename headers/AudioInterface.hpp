#pragma once
#include <portaudio.h>
#include <queue>
#include <vector>
#include "ImageParser.hpp"

constexpr int SAMPLE_RATE = 44100;

class AudioInterface {
public:
    bool IsValid;

private:
    std::queue<double> AudioBuff;
    ImageParser& parser;
    PaStream* stream;
    PaError err;

public:
    explicit AudioInterface( ImageParser& parser_ );
    ~AudioInterface() = default;
    void PlayStream();
    void EndStream();
    void PushAudioQueue( std::vector<double>& WaveTable );

private:
    void CatchErr() const;
    int Callback(const void* input,
                 void* output,
                 unsigned long frameCount,
                 const PaStreamCallbackTimeInfo* timeInfo,
                 PaStreamCallbackFlags statusFlags);

    static int PaCallback(const void* input,
                          void* output,
                          unsigned long frameCount,
                          const PaStreamCallbackTimeInfo* timeInfo,
                          PaStreamCallbackFlags statusFlags,
                          void* userData) {
        return ((AudioInterface*)userData)->Callback(input, output, frameCount, timeInfo, statusFlags);
    }
};