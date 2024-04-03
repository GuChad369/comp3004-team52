#include "site.h"

Site::Site() {

}


void Site::deliverTreatment(int treatmentFrequency){
    this->treatmentFrequency = treatmentFrequency;
    qInfo()<<"delivering treatment in"<<treatmentFrequency<<"hz.";
}
