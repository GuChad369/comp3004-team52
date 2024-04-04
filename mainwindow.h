#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QColor>
#include <QThread>
#include <QTimer>
#include <QSound> // QT += multimedia in Team52.pro file
#include <QListWidget>
#include "session.h"
#include <QtConcurrent/QtConcurrent>
#include <QFuture>
#include <QFutureWatcher>
#include <QMutex>
#include <QWaitCondition>
#include <QDateTime>
#include <QDate>
#include <QTime>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    /*
     * NEW SESSION
    */
    QTimer* pauseNewSessionTimer;               // set timer for pause to off the device
    QFutureWatcher<void> newSessionWatcher;     // monitor the session calculation thread result
    QFutureWatcher<void> checkWatcher;          // monitor the check thread result
    QMutex newSessionMutex;                     // for pause the session thread
    QWaitCondition newSessionPauseCondition;    // for pause the session thread
    bool newSessionPaused;                      // record if session thread was paused
    vector<Session *> sessions;                 // store the session obj
    bool isStop;                                // record if the session was terminated to make all child thread stop
    bool newSessionSuccess;                     // record the session result to do different function
    QTime sessionTime;
    double progress;
    QTimer* sessionTimer;
    double duration;                            // record the second cost of one session

    void showMenuSelectionOne();
    void closeMenuSelectionOne();
    void doNewSession();
    bool initiateSession();
    bool doCalculate();
    void newSessionCompleted();
    void pauseNewSessionTimerStart();
    void pauseNewSessionTimerEnd();


    /*
     * SESSION LOG
    */
    void showMenuSelectionTwo();
    void closeMenuSelectionTwo();

    /*
     * TIME AND DATE
    */
    QDate deviceDate;
    QTime deviceTime;
    QTimer* deviceTimer;

    void showMenuSelectionThree();
    void closeMenuSelectionThree();
    void updateDateTime();

    /*
     * LIGHT
    */
    QTimer* redFlashTimer;
    QTimer* greenFlashTimer;

    void lightOn(QGraphicsView* gv, const string& color);
    void lightOff(QGraphicsView* gv);
    void redLightflashOn();
    void redLightflashOff();
    void greenLightflashOn();
    void greenLightflashOff();
    void initialTimer();

    /*
     * BATTERY
    */
    QMutex batteryMutex;                    // for pause the battery thread
    QWaitCondition batteryPauseCondition;   // for pause the battery thread
    bool batteryPaused;                     // for pause the battery thread
    double batteryVolume;                   // record the battery value
    bool batteryInitiate;                   // for the first time ON to run battery thread

    void batteryAction();
    void pauseBattery();
    void resumeBattery();

    /*
     * Utils
    */
    bool powerValue;                        // record if the device is ON

    void powerOff();
    void showMenuSelection();
    void closeMenuSelection();
    void closeScreenAll();
    void beep();


    /*
     * EEG
     */
    bool isConnect;                             // record if exist connection

    /*
     * PC
     */
    vector<Session *> pcSessions;            // record pc data

signals:
    /*
     * child thread can not directly use parent timer and crate object
     * use signal to make child emit the signal
    */
    void signalBlueLightOn();
    void signalBlueLightOff();
    void signalRedLightFlashOn();
    void signalRedLightFlashOff();
    void signalGreenLightFlashOn();
    void signalGreenLightFlashOff();
    void signalBeep();
    void signalUpdateBattery();
    void signalUpdateProgress();
    void signalSessionTimerInitial();
    void signalSessionTimerStart();
    void signalSessionTimerPause();



private slots:
    /*
     * NEW SESSION
    */
    void pauseTask();
    void resumeTask();
    void stopTask();
    void exitNewSession();
    void AutoOff();
    void checkConnection();
    void updateProgress();
    void sessionTimerInitial();
    void sessionTimerStart();
    void sessionTimerPause();

    /*
     * TIME AND DATE
    */
    void increaseDateTime();
    void decreaseDateTime();

    /*
     * Light
    */
    void blueLightOn();
    void blueLightOff();

    /*
     * Battery
     */
    void updateBattery();

    /*
     * Utils
    */
    void power();
    void doubleClickMenu();
    void showMenu();

    /*
     * PC
    */
    void submitData();

};
#endif // MAINWINDOW_H
