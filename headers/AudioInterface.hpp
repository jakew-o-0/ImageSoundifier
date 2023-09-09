#pragma once
#include "AudioInterface.hpp"
#include <portaudio.h>
#include "ImageParser.hpp"
#include <vector>

constexpr int SAMPLE_RATE = 44100;

class AudioInterface {
private:
    std::vector<chord>& WaveTable;
    int WaveTablePos = 0;
    PaStream* stream;
    PaError err;

public:
    explicit AudioInterface(std::vector<chord>& Table);
    ~AudioInterface() = default;
    void PlayStream();

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