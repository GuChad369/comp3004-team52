#ifndef WAVESIMULATOR_H
#define WAVESIMULATOR_H
#include<QObject>
#include "frequencyBands.h"


class WaveSimulator{

public:
    WaveSimulator(FrequencyBand);
    double generateWave();
    double calculateBaseline();


    //void deliverTreatment(int treatmentFrequency);


private:
    FrequencyBand currentBand;
    static const int N = 32;//number of samples
    static const int Fs = 256; //sampling frequency, google said you can do 128,256,512,1024Hz
    int frequency; // f1, f2, f3
    int amplitude;// a1, a2, a3
    std::vector<double> signal;
    std::vector<double> frequencies;
    std::vector<double> amplitudes;
    int generateRandomFrequency();
    int generateRandomAmplitude();





};
#endif // WAVESIMULATOR_H
