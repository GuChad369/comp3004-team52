#ifndef FREQUENCYBANDS_H
#define FREQUENCYBANDS_H

// In my design, every single session, all frequency of 21 electrodes fall into the same band
// because I think at the very short time session, the 21 electrodes signal will not change too much, I don't know whether it is scientific or not.
struct FrequencyBand {
    int min;
    int max;
};

const FrequencyBand DELTA = {1, 4};
const FrequencyBand THETA = {4, 7};
const FrequencyBand ALPHA = {8, 12};
const FrequencyBand SIGMA = {12, 16};
const FrequencyBand BETA = {13, 30};

#endif // FREQUENCYBANDS_H
