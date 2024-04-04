#ifndef WAVESIMULATOR_H
#define WAVESIMULATOR_H
#include<QObject>
#include "frequencyBands.h"


class WaveSimulator{

public:
    WaveSimulator(FrequencyBand);
    int generateWave();


    //void deliverTreatment(int treatmentFrequency);


private:
    FrequencyBand currentBand;
    static const int N = 32;//number of samples
    static const int Fs = 256; //sampling frequency, google said you can do 128,256,512,1024Hz
    int baselineFrequency; // what we want
    std::vector<double> signal;
    int generateRandomFrequency();



};
#endif // WAVESIMULATOR_H
