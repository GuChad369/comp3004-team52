#include <QRandomGenerator>
#include<QDebug>
#include "waveSimulator.h"
#include<cmath>


WaveSimulator:: WaveSimulator(FrequencyBand band):
    currentBand(band){
}

//apply this frequency to the math formula in generateWave()
int WaveSimulator::generateRandomFrequency(){
    // Generate a random integer between the specific bands.

    int range = static_cast<int>(currentBand.max - currentBand.min) + 1;
    frequency = static_cast<int>(currentBand.min) + QRandomGenerator::global()->bounded(range);
    return frequency;
}

int WaveSimulator::generateRandomAmplitude() {
    // Generate a random amplitude between 10uV and 100uV
    int minAmp = 10.0;
    int maxAmp = 100.0;
    int range = maxAmp - minAmp;
    amplitude = minAmp + (QRandomGenerator::global()->bounded(range));
    return amplitude;
}


//we simulate a wave, but we don't really use it in our program. Just for more related to the real life
//in the real world, we got a wave, then do all the calculation analysis to obtain Dominant frequency(baseline frequency)
double WaveSimulator::generateWave() {
    signal.clear();
    frequencies.clear();
    amplitudes.clear();

    // Generating random frequencies and amplitudes for f1, f2, f3
    for(int j = 0; j < 3; ++j) {
        frequencies.push_back(generateRandomFrequency());
        amplitudes.push_back(generateRandomAmplitude());
    }

//sum of 3 sin waves
    for(int i = 0; i < N; ++i) {
        double waveform = 0.0;
        for(int j = 0; j < 3; ++j) {
            waveform += amplitudes[j] * sin(2 * M_PI * frequencies[j] * i / Fs);
        }
        signal.push_back(waveform);
    }
    // Here we simulate the waveform but don't use it further
    return calculateBaseline();
}

double WaveSimulator::calculateBaseline() {
    double numerator = 0.0;
    double denominator = 0.0;

    for(int i = 0; i < 3; ++i) {
        numerator += static_cast<double>(frequencies[i]) * std::pow(static_cast<double>(amplitudes[i]), 2);
        denominator += std::pow(static_cast<double>(amplitudes[i]), 2);
    }

    return numerator / denominator;}






