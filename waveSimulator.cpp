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
    baselineFrequency = static_cast<int>(currentBand.min) + QRandomGenerator::global()->bounded(range);
    return baselineFrequency;
}


//we simulate a wave, but we don't really use it in our program. Just for more related to the real life
//in the real world, we got a wave, then do all the calculation analysis to obtain Dominant frequency(baseline frequency)
int WaveSimulator:: generateWave(){
    signal.clear();
    baselineFrequency = generateRandomFrequency();
    for(int i = 0; i < N; i++){
        signal.push_back(sin(2* M_PI * baselineFrequency*i/Fs)); // math formula
    }
    return baselineFrequency;
}







