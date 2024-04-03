#ifndef SITE_H
#define SITE_H

#include<QDebug>

class Site{

public:
    Site();
    void deliverTreatment(int treatmentFrequency);


private:

    int treatmentFrequency;

};


#endif // SITE_H
