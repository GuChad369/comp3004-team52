#ifndef SESSION_H
#define SESSION_H

#include <string>
#include <iostream>
#include <ctime>
#include <iomanip>
#include <vector>
#include <QObject>
#include "waveSimulator.h"
#include "analysisWave.h"
#include "site.h"
#include "frequencyBands.h"
#include <QDebug>
#include <QTimer>
#include <vector>
#include <QRandomGenerator>

using namespace std;

class Session: public QObject
{Q_OBJECT
public:
    //    Session(const string& date, const string& time,QObject *parent = nullptr);
    Session(const string& date, const string& time);
    ~Session();

    const string& getDate() const;
    const string& getTime() const;
    bool getNeedDeleted();
    void setNeedDeleted(bool b);
    int getCurrentSite();
    void setCurrentSite(int c);
    int getTreatmentCounter();
    void setTreatmentCounter(int t);
    const string& getTitle() const;
    void setTitle(const string& t);

    void startSession();
    int onetimeTreatment();
    void calculateBeforeSessionBaselines();
    void calculateAfterSessionBaselines();
    void calculateOverallBaseline(QVector<int>&  baselines);
    void printPCRecords();

    QVector<int> beforeSessionBaselines = QVector<int>(21);
    QVector<int> afterSessionBaselines = QVector<int>(21);




private:
    string date;
    string time;
    bool needDeleted;
    string title;

    QVector<WaveSimulator*> waves;
    AnalysisWave* analysis;
    Site* site;

    int currentSite;
    static const int totalSites = 21;


    int treatmentCounter;
    static const int treatmentIntervals = 16;


};

#endif // SESSION_H
