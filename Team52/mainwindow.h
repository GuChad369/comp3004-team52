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
    bool isConnect;                             // record if exist connection
    bool isStop;                                // record if the session was terminated to make all child thread stop
    bool newSessionSuccess;                     // record the session result to do different function

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

    void showMenuSelectionThree();
    void closeMenuSelectionThree();
    void updateDateTime();

    /*
     * LIGHT
    */
    QTimer* flashTimer;                     // make light flash

    void lightOn(QGraphicsView* gv, const string& color);
    void lightOff(QGraphicsView* gv);
    void lightflashOn(QGraphicsView* gv, const QString& color);
    void lightflashOff(QGraphicsView* gv);

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

signals:
    /*
     * child thread can not directly use parent timer and crate object
     * use signal to make child emit the signal
    */
    void signalLightFlashOn(QGraphicsView* gv, const QString& color);
    void signalLightFlashOff(QGraphicsView* gv);
    void signalBeep();


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

    /*
     * TIME AND DATE
    */
    void increaseDateTime();
    void decreaseDateTime();

    /*
     * Utils
    */
    void power();
    void doubleClickMenu();
    void showMenu();



    /*
     * EGG
    */
    void toggleConnect();               // this is for a button to control the connection





    // will discard
    void test1();   // this now connect with toggleConnect can control the connection
    void test2();   // this is test for the window can response action
};
#endif // MAINWINDOW_H
