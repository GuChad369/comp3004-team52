#include "session.h"



Session::Session(const string& date, const string& time)
    : date(date), time(time), needDeleted(true),
      currentSite(0), treatmentCounter(0){

    waves = QVector<WaveSimulator*>();
    analysis = new AnalysisWave();
    site = new Site();
}

Session::~Session() {
    delete analysis;
    for (auto wave : waves) {
        delete wave;
    }
    delete site;
}


const string& Session::getDate() const{
    return date;
};

const string& Session::getTime() const{
    return time;
};

bool Session::getNeedDeleted(){
    return needDeleted;
}
void Session::setNeedDeleted(bool b){
    this->needDeleted = b;
}
int  Session::getCurrentSite(){
    return this->currentSite;
}
void  Session::setCurrentSite(int c){
    this->currentSite = c;
}
int Session::getTreatmentCounter(){
    return this->treatmentCounter;
}
void Session::setTreatmentCounter(int t){
    this->treatmentCounter = t;
}
const string& Session::getTitle() const{
    return this->title;
}
void Session::setTitle(const string &t){
    this->title=t;
}

void Session::startSession() {
    qInfo()<<"--------------------------------Staring session-------------------------------";

    //before the session start, random choose a band, to make sure all frequency of 21 sites are within the same band.
    std::vector<FrequencyBand> bands = {DELTA, THETA, ALPHA, SIGMA, BETA};
    int index = QRandomGenerator::global()->bounded(static_cast<int>(bands.size()));
    FrequencyBand sessionBand = bands[index];

    waves.clear();

    // Create Site objects for this session with the selected frequency band
    for (int i = 0; i < totalSites; ++i) {
        waves.push_back(new WaveSimulator(sessionBand));
    }
}

int Session::onetimeTreatment(){
    if(treatmentCounter<treatmentIntervals){
        int offset = 5;
        double newBaseline = analysis->getBaseline(waves[currentSite]);
        double treatmentFrequency = newBaseline + offset;

        qInfo()<<"Site"<<currentSite + 1<<":: round"<<(treatmentCounter +1)<<"/16,"<<"Begin treating: Dominant Frequency ="<<newBaseline<< ", Treatment Frequency after add offset ="<<treatmentFrequency;
        site->deliverTreatment(treatmentFrequency);
        return 0;
    }
    return 1;
}

void Session::calculateOverallBaseline(QVector<int>&  baselines){

    for (int i =0; i<waves.size();i++){
        baselines[i] = analysis->getBaseline(waves[i]);
    }
}

void Session::calculateBeforeSessionBaselines(){

    calculateOverallBaseline(beforeSessionBaselines);
}

void Session::calculateAfterSessionBaselines(){
     calculateOverallBaseline(afterSessionBaselines);
}

//this is  for the test purpose, those data should show in PC UI
void Session::printPCRecords() {
    for (int i = 0; i < waves.size(); ++i) {
        qInfo() << "Site" << i + 1 << ", Initial Value:" << beforeSessionBaselines[i] << "; Final Value:" << afterSessionBaselines[i];
    }
}


