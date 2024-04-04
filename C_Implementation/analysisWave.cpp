#include "analysisWave.h"
//this class is for simulating the process of analyzing a wave, in the end, we can got a dominant frequency HZ
//in real wold, this process include FFT, and frequency power spectrum, etc.
AnalysisWave:: AnalysisWave(){}


int AnalysisWave::getBaseline(WaveSimulator* wave){

    return wave->generateWave();

}

