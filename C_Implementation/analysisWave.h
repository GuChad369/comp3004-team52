#ifndef ANALYSISWAVE_H
#define ANALYSISWAVE_H

#include "waveSimulator.h"

class AnalysisWave{


public:
    AnalysisWave();
    double getBaseline(WaveSimulator* wave);
};
#endif // ANALYSISWAVE_H
