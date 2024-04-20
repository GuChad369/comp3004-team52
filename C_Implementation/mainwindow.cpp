#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>


/*
 *
 *
 *
 *
 *
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,newSessionPaused(false)
    ,isStop(true)
    ,progress(0.0)
    ,batteryPaused(false)
    ,batteryVolume(100.0)
    ,batteryInitiate(false)
    ,powerValue(false)
    ,isConnect(false)

{
    ui->setupUi(this);

    // increase QThreadPool, otherwise cant work for multi-thread
    QThreadPool::globalInstance()->setMaxThreadCount(20);

    /*
     * NEW SESSION
     *
    */
    // hide NEW SESSION
    ui->interface_menu_selection0_time->setVisible(false);
    ui->interface_menu_selection0_progress->setVisible(false);
    ui->interface_menu_selection0_completed->setVisible(false);
    connect(ui->interface_pause, &QPushButton::clicked, this, &MainWindow::pauseTask);
    connect(ui->interface_start, &QPushButton::clicked, this, &MainWindow::resumeTask);
    connect(ui->interface_stop, &QPushButton::clicked, this, &MainWindow::stopTask);
    sessionTimer = new QTimer(this);

    /*
     * SESSION LOG
     *
    */
    // hide SESSION LOG
    ui->interface_menu_selection1->setVisible(false);

    /*
     * TIME AND DATE
     *
    */
    // initial date and time
    deviceDate = QDate::currentDate();
    deviceTime = QTime::currentTime();
    // hide TIME AND DATE
    ui->interface_menu_selection2_frame->setVisible(false);
    // initial the date and time to the window
    updateDateTime();
    deviceTimer = new QTimer(this);
    connect(deviceTimer, &QTimer::timeout, this, [this]() {
        deviceTime = deviceTime.addSecs(1);
    });
    deviceTimer->start(1000);

    /*
     * Light
     *
    */
    redFlashTimer = new QTimer(this);
    greenFlashTimer = new QTimer(this);
    initialTimer();
    redLightflashOff();
    greenLightflashOff();


    /*
     * Battery
     *
    */
    connect(ui->interface_recharge, &QPushButton::clicked, this, &MainWindow::rechargeBattery);

    // for light since thread cant call parent timer directly
    connect(this, &MainWindow::signalBlueLightOn, this, &MainWindow::blueLightOn, Qt::QueuedConnection);
    connect(this, &MainWindow::signalBlueLightOff, this, &MainWindow::blueLightOff, Qt::QueuedConnection);
    connect(this, &MainWindow::signalRedLightFlashOn, this, &MainWindow::redLightflashOn, Qt::QueuedConnection);
    connect(this, &MainWindow::signalRedLightFlashOff, this, &MainWindow::redLightflashOff, Qt::QueuedConnection);
    connect(this, &MainWindow::signalGreenLightFlashOn, this, &MainWindow::greenLightflashOn, Qt::QueuedConnection);
    connect(this, &MainWindow::signalGreenLightFlashOff, this, &MainWindow::greenLightflashOff, Qt::QueuedConnection);
    // for beep, same reason
    connect(this, &MainWindow::signalBeep, this, &MainWindow::beep, Qt::QueuedConnection);
    // for new session
    connect(this, &MainWindow::signalUpdateProgress, this, &MainWindow::updateProgress, Qt::QueuedConnection);
    connect(this, &MainWindow::signalSessionTimerInitial, this, &MainWindow::sessionTimerInitial, Qt::QueuedConnection);
    connect(this, &MainWindow::signalSessionTimerStart, this, &MainWindow::sessionTimerStart, Qt::QueuedConnection);
    connect(this, &MainWindow::signalSessionTimerPause, this, &MainWindow::sessionTimerPause, Qt::QueuedConnection);
    // for battery
    connect(this, &MainWindow::signalUpdateBattery, this, &MainWindow::updateBattery, Qt::QueuedConnection);




    /*
     * Utils
     *
    */
    // hide the menu initially
    ui->interface_menu_selection->setVisible(false);
    connect(ui->interface_power, &QPushButton::clicked, this, &MainWindow::power);
    connect(ui->interface_menu, &QPushButton::clicked, this, &MainWindow::showMenu);



    /*
     * EEG
     */
    connect(ui->toggleConnection, &QPushButton::toggled, [this](bool checked) {
        isConnect = !isConnect;
        ui->toggleConnection->setText(checked ? "On" : "Off");
    });

    /*
     * PC
     */

    //for pc ui test
    connect(ui->pc_submit, &QPushButton::clicked, this, &MainWindow::pc_submit_clicked);
    connect(ui->pc_monitor_show, &QListWidget::itemDoubleClicked, this, &MainWindow::doubleClickPc);

    /*
     * Waveform graph
     */
    setupGraphView();

}

MainWindow::~MainWindow()
{
    delete ui;
}



/*
 * NEW SESSION
 *
*/
void MainWindow::showMenuSelectionOne(){
    bool flag = ui->interface_menu_selection0_time->isVisible();

    if(flag){
        return;
    }else{
        ui->interface_menu_selection0_time->setVisible(true);
        ui->interface_menu_selection0_progress->setVisible(true);
    }

}
void MainWindow::closeMenuSelectionOne(){
    bool flag = ui->interface_menu_selection0_time->isVisible();

    if(flag){
        ui->interface_menu_selection0_time->setVisible(false);
        ui->interface_menu_selection0_progress->setVisible(false);
    }else{

    }
}
void MainWindow::checkConnection(){
    while(!isStop){
        qDebug()<<"check connection";
        if(isConnect){
            // light the blue
            emit signalBlueLightOn();
            emit signalRedLightFlashOff();
            QThread::msleep(1000);
        }else{
            qDebug()<<"wait connection";
            // close blue
            emit signalBlueLightOff();
            emit signalRedLightFlashOn();

            // pause action
            pauseTask();
            // wait the connection for 5 minutes
            // Get the current time
            QDateTime startTime = QDateTime::currentDateTime();
            while(!isStop){
                QDateTime currentTime = QDateTime::currentDateTime();
                qint64 elapsedSeconds = startTime.secsTo(currentTime);
                if (elapsedSeconds >= 5*60) {
                    // fail
                    return;
                }
                if(isConnect){
                    resumeTask();
                    // break, continue to check the connection
                    break;
                }

                emit signalBeep();
                QThread::msleep(1000);
            }
        }
    }
}
void MainWindow::doNewSession(){
    // initate the session
    bool flag = initiateSession();

    if(flag){
        if(doCalculate()){
            Session *newestSession = sessions.back();
            newestSession->setNeedDeleted(false);
            // success
            newSessionSuccess = true;
        }
    }
}
bool MainWindow::initiateSession(){
    if(isConnect){
        // create new session
        // get date and time
        QString date = deviceDate.toString("yyyy-MM-dd");
        QString time = deviceTime.toString("HH:mm:ss");
        Session* s = new Session(date.toStdString(),time.toStdString());
        QString title = date + " " + time;
        s->setTitle(title.toStdString());
        sessions.push_back(s);
        sessionTime = QTime(0,0,46);
        emit signalSessionTimerInitial();
        progress = 0.0;
        emit updateProgress();
        return true;
    }else{
        // wait the connection for 5 minutes
        // Get the current time
        QDateTime startTime = QDateTime::currentDateTime();
        while(!isStop){
            QDateTime currentTime = QDateTime::currentDateTime();
            qint64 elapsedSeconds = startTime.secsTo(currentTime);
            if (elapsedSeconds >= 5*60) {
                // fail
                return false;
            }
            if(isConnect){
                return initiateSession();
            }
            QThread::msleep(1000);
        }
    }
    return false;
}
bool MainWindow::doCalculate(){
    while(!isStop){
        cout<<"detected no error with device functions"<<endl;
        emit signalSessionTimerStart();

        // get the session
        Session *currSession;
        if (!sessions.empty()) {
            currSession = sessions.back();
        }else{
            return false;
        }

        currSession->startSession();
        // function used to calculate overall baseline for 21 sites, will be showed in PC UI
        currSession->calculateBeforeSessionBaselines();
        currSession->setCurrentSite(0);
        for (int i = 0; i <5;i++ ) {

            if(isStop){
                return false;
            }


            newSessionMutex.lock();
            if (newSessionPaused) {
                emit signalSessionTimerPause();
                newSessionPauseCondition.wait(&newSessionMutex);
                emit signalSessionTimerStart();
            }
            newSessionMutex.unlock();



            QThread::msleep(1000);
            progress += 2.17;
            emit signalUpdateProgress();
        }


        // green light flash
        emit signalGreenLightFlashOn();
        for (int st = 0; st < 21; st++) {

            if(isStop){
                return false;
            }
            //for update waveform
            currSession->setTreatmentCounter(0);
            for (int i = 0; i < 16; i++ ) {
                if(isStop){
                    return false;
                }
                // do the pause
                newSessionMutex.lock();
                if (newSessionPaused) {
                    emit signalGreenLightFlashOff();
                    emit signalSessionTimerPause();
                    newSessionPauseCondition.wait(&newSessionMutex);
                    emit signalGreenLightFlashOn();
                    emit signalSessionTimerStart();

                }
                newSessionMutex.unlock();

                int succ = currSession->onetimeTreatment();
                if(succ){
                    return false;
                }
                currSession->setTreatmentCounter(currSession->getTreatmentCounter()+1);


                // 1/16 second delay moving to next round
                QThread::msleep(1000 / 16);

            }
            progress += 2.17;
            emit signalUpdateProgress();

            qInfo()<<"Site"<<currSession->getCurrentSite()+1<<"has finished treatment.";
            currSession->setCurrentSite(currSession->getCurrentSite()+1);

            QThread::msleep(1000);//1 second delay moving to next site
            progress += 2.17;
            emit signalUpdateProgress();

        }
        // close light
        emit signalGreenLightFlashOff();

        qInfo() << "------------------------------Treatment finished for all sites.------------------------------";
        currSession->calculateAfterSessionBaselines();//this is the function calculate overall baseline after session.

        progress = 100;
        emit signalUpdateProgress();
        emit signalSessionTimerPause();
        QThread::msleep(1000);

        return true;
    }
    return false;
}
void MainWindow::pauseTask() {
    if(!powerValue || isStop){
        return;
    }
    newSessionMutex.lock();
    newSessionPaused = true;
    newSessionMutex.unlock();

    if (QThread::currentThread() != QCoreApplication::instance()->thread()) {
        // Called by a child thread
        return;
    }
    pauseNewSessionTimerStart();
}
void MainWindow::pauseNewSessionTimerStart(){
    // set timer
    if(pauseNewSessionTimer!=nullptr){
        disconnect(pauseNewSessionTimer, &QTimer::timeout, this, &MainWindow::AutoOff);
        pauseNewSessionTimer->stop();
        delete pauseNewSessionTimer;
        pauseNewSessionTimer = nullptr;
    }
    pauseNewSessionTimer = new QTimer(this);
    pauseNewSessionTimer->setInterval(60000); // 60000 milliseconds = 60 seconds
    connect(pauseNewSessionTimer, &QTimer::timeout, this, &MainWindow::AutoOff);
    pauseNewSessionTimer->start();
}
void MainWindow::pauseNewSessionTimerEnd(){
    if(pauseNewSessionTimer!=nullptr){
        disconnect(pauseNewSessionTimer, &QTimer::timeout, this, &MainWindow::AutoOff);
        pauseNewSessionTimer->stop();
        delete pauseNewSessionTimer;
        pauseNewSessionTimer = nullptr;
    }
}
void MainWindow::resumeTask() {
    if(!powerValue || isStop){
        return;
    }
    newSessionMutex.lock();
    newSessionPaused = false;
    newSessionPauseCondition.wakeAll();
    newSessionMutex.unlock();

    if (QThread::currentThread() != QCoreApplication::instance()->thread()) {
        // Called by a child thread
        return;
    }

    // close timer
    pauseNewSessionTimerEnd();
}
void MainWindow::stopTask(){
    if(!powerValue || isStop){
        return;
    }
    isStop = true;
    AutoOff();
}
void MainWindow::newSessionCompleted(){
    isStop = true;
    // close light
    blueLightOff();
    redLightflashOff();
    greenLightflashOff();
    if(newSessionSuccess){

        // show complete component
        ui->interface_menu_selection0_completed->setVisible(true);
        // connect event
        connect(ui->completed_exit, &QPushButton::clicked, this, &MainWindow::exitNewSession);
    }else {
        AutoOff();
    }
}
void MainWindow::AutoOff(){
    if(newSessionSuccess){
        return;
    }
    if(newSessionPaused){
        resumeTask();
    }
    isStop = true;
    sessionTimerPause();
    // delete the session
    if (!sessions.empty()) {
        Session *newestSession = sessions.back();
        if(newestSession->getNeedDeleted()){
            delete sessions.back();
            sessions.pop_back();
        }
    }
    // close light
    redLightflashOff();
    // close Timer
    pauseNewSessionTimerEnd();
    powerOff();
}
void MainWindow::exitNewSession(){
    closeMenuSelectionOne();
    // disconnect slot
    disconnect(ui->completed_exit, &QPushButton::clicked, this, &MainWindow::exitNewSession);
    // close this complete frame
    ui->interface_menu_selection0_completed->setVisible(false);
    showMenuSelection();
    newSessionSuccess = false;
}
void MainWindow::updateProgress(){
    // get value
    int currentValue = ui->interface_menu_selection0_progress->value();
    int changedInt = static_cast<int>(progress);

    if(changedInt == 100){
        return;
    }

    if(currentValue != changedInt){
        ui->interface_menu_selection0_progress->setValue(changedInt);
    }
}
void MainWindow::sessionTimerInitial(){
    disconnect(sessionTimer, &QTimer::timeout, nullptr, nullptr);
    connect(sessionTimer, &QTimer::timeout, this, [this]() {
        sessionTime = sessionTime.addSecs(-1);
        ui->interface_menu_selection0_time->setTime(sessionTime);
    });

}
void MainWindow::sessionTimerStart(){
    sessionTimer->start(1000);
}
void MainWindow::sessionTimerPause(){
    sessionTimer->stop();
}



/*
 * SESSION LOG
 */
void MainWindow::showMenuSelectionTwo(){
    bool flag = ui->interface_menu_selection1->isVisible();

    if(!flag){
        ui->interface_menu_selection1->setVisible(true);
        for (Session* s : sessions) {
            if(s != nullptr){
                QString itemText = QString::fromStdString(s->getTitle());

                // Check if an item with the same text already exists
                QList<QListWidgetItem*> existingItems = ui->interface_menu_selection1->findItems(itemText, Qt::MatchExactly);
                if (existingItems.isEmpty()) {
                    // No existing item with the same text, so add a new item
                    QListWidgetItem *newItem = new QListWidgetItem();
                    newItem->setText(itemText);
                    ui->interface_menu_selection1->addItem(newItem);
                }

                qInfo() << itemText;
                // print the result
                s->printPCRecords();
            }
        }
    }else{

    }


}
void MainWindow::closeMenuSelectionTwo(){
    bool flag = ui->interface_menu_selection1->isVisible();

    if(flag){
        ui->interface_menu_selection1->setVisible(false);
    }else{

    }
}

/*
 * TIME AND DATE
 */
void MainWindow::showMenuSelectionThree(){
    bool flag = ui->interface_menu_selection2_frame->isVisible();

    if(!flag){
        ui->interface_menu_selection2_frame->setVisible(true);
        connect(ui->interface_menu_selection2_increase, &QPushButton::clicked, this, &MainWindow::increaseDateTime);
        connect(ui->interface_menu_selection2_decrease, &QPushButton::clicked, this, &MainWindow::decreaseDateTime);

    }else{

    }
}
void MainWindow::closeMenuSelectionThree(){
    bool flag = ui->interface_menu_selection2_frame->isVisible();
    if(flag){
        disconnect(ui->interface_menu_selection2_increase, &QPushButton::clicked, this, &MainWindow::increaseDateTime);
        disconnect(ui->interface_menu_selection2_decrease, &QPushButton::clicked, this, &MainWindow::decreaseDateTime);
        ui->interface_menu_selection2_frame->setVisible(false);
    }else{

    }
}
// manipulate Date and time
void MainWindow::updateDateTime(){
    ui->interface_menu_selection2_date->setDate(deviceDate);
    ui->interface_menu_selection2_time->setTime(deviceTime);
}
void MainWindow::increaseDateTime(){
    QString selectedComponent = ui->interface_menu_selection2_combo->currentText();
    if (selectedComponent == "Year") {
        deviceDate = deviceDate.addYears(1);
    } else if (selectedComponent == "Month") {
        deviceDate = deviceDate.addMonths(1);
    } else if (selectedComponent == "Day") {
        deviceDate = deviceDate.addDays(1);
    }else if (selectedComponent == "Hour") {
        deviceTime = deviceTime.addSecs(3600);
    }else if (selectedComponent == "Minute") {
        deviceTime = deviceTime.addSecs(60);
    }else if (selectedComponent == "Second") {
        deviceTime = deviceTime.addSecs(1);
    }
    updateDateTime();
}
void MainWindow::decreaseDateTime(){
    QString selectedComponent = ui->interface_menu_selection2_combo->currentText();
    if (selectedComponent == "Year") {
        deviceDate = deviceDate.addYears(-1);
    } else if (selectedComponent == "Month") {
        deviceDate = deviceDate.addMonths(-1);
    } else if (selectedComponent == "Day") {
        deviceDate = deviceDate.addDays(-1);
    }else if (selectedComponent == "Hour") {
        deviceTime = deviceTime.addSecs(-3600);
    }else if (selectedComponent == "Minute") {
        deviceTime = deviceTime.addSecs(-60);
    }else if (selectedComponent == "Second") {
        deviceTime = deviceTime.addSecs(-1);
    }
    updateDateTime();
}


/*
 * Light
 */
void MainWindow::lightOn(QGraphicsView* gv, const string& color){
    if(gv){
        QString styleSheet = QString("QGraphicsView { background-color: %1; }").arg(QString::fromStdString(color));
        gv->setStyleSheet(styleSheet);
    }
}
void MainWindow::lightOff(QGraphicsView* gv){
    if(gv){
        QString currentStyleSheet = gv->styleSheet();
        if (!currentStyleSheet.contains("background-color:gray;")) {
            gv->setStyleSheet("QGraphicsView { background-color:gray; }");
        }
    }
}
void MainWindow::initialTimer() {
    // Store the original and flash colors in properties for later use
    ui->interface_red->setProperty("originalColor", ui->interface_red->styleSheet());
    ui->interface_red->setProperty("flashColor", QString("QGraphicsView { background-color: %1; }").arg("red"));
    ui->interface_green->setProperty("originalColor", ui->interface_green->styleSheet());
    ui->interface_green->setProperty("flashColor", QString("QGraphicsView { background-color: %1; }").arg("green"));

    // Connect the timer's timeout signal to a lambda function that toggles the color for the red view
    connect(redFlashTimer, &QTimer::timeout, this, [this]() {
        static bool flashState = false;
        QGraphicsView* gv = ui->interface_red; // Assuming interface_red is a QGraphicsView*
        if (flashState) {
            gv->setStyleSheet(gv->property("originalColor").toString());
        } else {
            gv->setStyleSheet(gv->property("flashColor").toString());
        }
        flashState = !flashState;
    });
    redFlashTimer->start(100);

    // Connect the timer's timeout signal to a lambda function that toggles the color for the green view
    connect(greenFlashTimer, &QTimer::timeout, this, [this]() {
        static bool flashState = false;
        QGraphicsView* gv = ui->interface_green; // Assuming interface_green is a QGraphicsView*
        if (flashState) {
            gv->setStyleSheet(gv->property("originalColor").toString());
        } else {
            gv->setStyleSheet(gv->property("flashColor").toString());
        }
        flashState = !flashState;
    });
    greenFlashTimer->start(100);
}

void MainWindow::redLightflashOn(){
    redFlashTimer->start();

}
void MainWindow::redLightflashOff(){

    redFlashTimer->stop();  // Stop the flashing timer
    QVariant originalColor = ui->interface_red->property("originalColor");
    if (originalColor.isValid()) {
        ui->interface_red->setStyleSheet(originalColor.toString());  // Restore the original color if it exists
    }


}
void MainWindow::greenLightflashOn(){
    greenFlashTimer->start();
}
void MainWindow::greenLightflashOff(){

    greenFlashTimer->stop();  // Stop the flashing timer
    QVariant originalColor = ui->interface_green->property("originalColor");
    if (originalColor.isValid()) {
        ui->interface_green->setStyleSheet(originalColor.toString());  // Restore the original color if it exists
    }
}
void MainWindow::blueLightOn(){
    lightOn(ui->interface_blue,"blue");

}
void MainWindow::blueLightOff(){
    lightOff(ui->interface_blue);
}


/*
 * BATTERY
 */
void MainWindow::updateBattery(){
    // get value
    int currentValue = ui->interface_battery->value();
    int changedInt = static_cast<int>(batteryVolume);
    if(currentValue != changedInt){
        ui->interface_battery->setValue(changedInt);
    }
    if(changedInt <= 0){
        AutoOff();
    }

    // show warning
    if(changedInt < 10){
        ui->interface_battery->setStyleSheet(
                    "QProgressBar {"
                    "   border: 2px solid grey;"
                    "   border-radius: 5px;"
                    "   background-color: #FFFFFF;"
                    "}"
                    "QProgressBar::chunk {"
                    "   background-color: #FF0000;" // Red color
                    "}"
                    );
    }
}
void MainWindow::batteryAction(){
    // duration is 33 minutes
    while(1){
        qDebug()<<"battery: "<< batteryVolume;
        batteryMutex.lock();
        if (batteryPaused) {
            batteryPauseCondition.wait(&batteryMutex);
        }
        batteryMutex.unlock();


        // update value
        batteryVolume -= 0.8;

        emit signalUpdateBattery();

        QThread::msleep(1000);
    }
}
void MainWindow::pauseBattery(){

    batteryMutex.lock();
    batteryPaused = true;
    batteryMutex.unlock();
}
void MainWindow::resumeBattery(){
    batteryMutex.lock();
    batteryPaused = false;
    batteryPauseCondition.wakeAll();
    batteryMutex.unlock();
}
void MainWindow::rechargeBattery(){
    // must power off
    if(powerValue){
        return;
    }
    batteryVolume = 100;
    ui->interface_battery->setStyleSheet("");
    updateBattery();
}



/*
 * Utils
 *
*/
void MainWindow::power(){
    if(batteryVolume <= 0){
        return ;
    }
    if(powerValue){

        AutoOff();
    }else{
        powerValue = true;

        lightOn(ui->interface_blue, "blue");
        lightOn(ui->interface_green, "green");
        lightOn(ui->interface_red, "red");
        QCoreApplication::processEvents();
        QThread::msleep(500);
        lightOff(ui->interface_blue);
        lightOff(ui->interface_green);
        lightOff(ui->interface_red);

        showMenuSelection();



        // first time initiate battery
        if(!batteryInitiate){
            batteryInitiate = true;
            // run battery action
            QFuture<void> future = QtConcurrent::run([this](){
                this->batteryAction();
            });
            pauseBattery();
        }


        resumeBattery();
    }
}
void MainWindow::powerOff(){
    powerValue = false;

    lightOn(ui->interface_blue, "blue");
    lightOn(ui->interface_green, "green");
    lightOn(ui->interface_red, "red");
    QCoreApplication::processEvents();
    QThread::msleep(500);
    lightOff(ui->interface_blue);
    lightOff(ui->interface_green);
    lightOff(ui->interface_red);

    closeScreenAll();

    pauseBattery();

}

// manipulate the menu selection
void MainWindow::showMenuSelection(){
    bool flag = ui->interface_menu_selection->isVisible();

    if(flag){
        return;
    }else{
        ui->interface_menu_selection->setVisible(true);
        connect(ui->interface_menu_selection, &QListWidget::itemDoubleClicked, this, &MainWindow::doubleClickMenu);
    }
}
void MainWindow::closeMenuSelection(){
    bool flag = ui->interface_menu_selection->isVisible();
    if(flag){
        disconnect(ui->interface_menu_selection, &QListWidget::itemDoubleClicked, this, &MainWindow::doubleClickMenu);
        ui->interface_menu_selection->setVisible(false);
    }
}

// beeping
void MainWindow::beep(){
    // change .pro file
    // include QSound
    // download the beep.wav
    QSound::play(":/beep.wav");
}

// close menu screen's all component
void MainWindow::closeScreenAll(){
    closeMenuSelection();
    closeMenuSelectionOne();
    ui->interface_menu_selection0_completed->setVisible(false);
    closeMenuSelectionTwo();
    closeMenuSelectionThree();

}

// click menu
void MainWindow::showMenu(){
    // for selection one cant exit
    if(!isStop){
        return;
    }
    closeScreenAll();
    showMenuSelection();
}

// manipulate the menu select action
void MainWindow::doubleClickMenu(){
    if(!powerValue){
        return;
    }

    int index = ui->interface_menu_selection->currentRow();

    closeMenuSelection();

    if(index == 0){
        showMenuSelectionOne();
        // start
        isStop =false;
        newSessionSuccess = false;
        // run check connection
        QFuture<void> futureCheck = QtConcurrent::run([this](){
            this->checkConnection();
        });
        // run action
        QFuture<void> futureSession = QtConcurrent::run([this](){
            this->doNewSession();
        });
        // monitor check result
        disconnect(&checkWatcher, &QFutureWatcher<void>::finished, this, &MainWindow::AutoOff);
        connect(&checkWatcher, &QFutureWatcher<void>::finished, this, &MainWindow::AutoOff);
        checkWatcher.setFuture(futureCheck);
        // monitor action result
        disconnect(&newSessionWatcher, &QFutureWatcher<void>::finished, this, &MainWindow::newSessionCompleted);
        connect(&newSessionWatcher, &QFutureWatcher<void>::finished, this, &MainWindow::newSessionCompleted);
        newSessionWatcher.setFuture(futureSession);
    }else if(index == 1){
        showMenuSelectionTwo();
    }else if(index == 2){
        showMenuSelectionThree();
    }
}


/*
 * PC
 */

void MainWindow::pc_submit_clicked(){
    if(!isStop){
        return;
    }
    for (Session* s : sessions) {
        if(s != nullptr){
            QString itemText = QString::fromStdString(s->getTitle());

            // Check if an item with the same text already exists
            QList<QListWidgetItem*> existingItems = ui->pc_monitor_show->findItems(itemText, Qt::MatchExactly);
            if (existingItems.isEmpty()) {
                // No existing item with the same text, so add a new item
                QListWidgetItem *newItem = new QListWidgetItem();
                newItem->setText(itemText);
                ui->pc_monitor_show->addItem(newItem);
            }
        }
    }


}
void MainWindow::doubleClickPc(){
    int index = ui->pc_monitor_show->currentRow();
    onGraphUpdate(index);
}
/*
 * Waveform graph
 *
*/

void MainWindow::setupGraphView()
{
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);

    ui->waveform_box->setLayout(new QVBoxLayout());
    ui->waveform_box->layout()->addWidget(view);
    // remove the fixed size for the sceneRect and replace it with a size that matches the waveform_box
    QRectF rect = QRectF(0, 0, ui->waveform_box->width(), ui->waveform_box->height());
    view->setSceneRect(rect);
}

void MainWindow::onGraphUpdate(int index)
{
    scene->clear(); //clear previous points
    qreal viewWidth = view->sceneRect().width();
    qreal viewHeight = view->sceneRect().height();
    float xStep = viewWidth / 21;
    float maxY = 0;

    Session * session = sessions[index];

    //find the maximum y-value across all afterSessionBaselines

    auto maxIt = max_element(session->afterSessionBaselines.begin(), session->afterSessionBaselines.end());
    if (maxIt != session->afterSessionBaselines.end()) {
        maxY = max(maxY, static_cast<float>(*maxIt));
    }


    QPointF prevPoint(0, viewHeight); //keep track of the previous point
    for (int i = 0; i < 21 && i < session->afterSessionBaselines.size(); ++i) {
        qreal x = xStep * i;
        qreal y = (session->afterSessionBaselines[i] / maxY) * viewHeight;
        QPointF point(x, viewHeight - y); // flip y to have the origin at the bottom left
        scene->addEllipse(point.x(), point.y(), 5, 5, QPen(), QBrush(Qt::red)); //change the color if needed

        if (i > 0) {
            //draw a line from the previous point to the current point
            QLineF line(prevPoint, point);
            scene->addLine(line, QPen(Qt::blue));
        }
        prevPoint = point; //update the previous point
    }

}
