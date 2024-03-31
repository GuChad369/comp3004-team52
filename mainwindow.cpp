#include "mainwindow.h"
#include "ui_mainwindow.h"



/*
 * this is the final version need to change
 * battery duration: 0.5 -> 0.05
 * 60 -> 5 * 60
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
    ,isConnect(false)
    ,isStop(true)
    ,batteryPaused(false)
    ,batteryVolume(100.0)
    ,batteryInitiate(false)
    ,powerValue(false)

{
    ui->setupUi(this);
    // increase QThreadPool, otherwise cant work for multi-thread
    QThreadPool::globalInstance()->setMaxThreadCount(10);

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

    /*
     * Light
     *
    */
    flashTimer = new QTimer(this);
    // for light since thread cant call parent timer directly
    connect(this, &MainWindow::signalLightFlashOn, this, &MainWindow::lightflashOn, Qt::QueuedConnection);
    connect(this, &MainWindow::signalLightFlashOff, this, &MainWindow::lightflashOff, Qt::QueuedConnection);
    // for beep, same reason
    connect(this, &MainWindow::signalBeep, this, &MainWindow::beep, Qt::QueuedConnection);



    /*
     * Utils
     *
    */
    // hide the menu initially
    ui->interface_menu_selection->setVisible(false);
    connect(ui->interface_power, &QPushButton::clicked, this, &MainWindow::power);
    connect(ui->interface_menu, &QPushButton::clicked, this, &MainWindow::showMenu);



    // just for test
    connect(ui->interface_up, &QPushButton::clicked, this, &MainWindow::test1);
    connect(ui->interface_down, &QPushButton::clicked, this, &MainWindow::test2);
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
        cout<<"check"<<endl;
        if(isConnect){
            // light the blue
            lightOn(ui->interface_blue,"blue");
            emit signalLightFlashOff(ui->interface_red);
            QThread::msleep(1000);
        }else{
            // close blue
            lightOff(ui->interface_blue);
            emit signalLightFlashOn(ui->interface_red, "red");

            // pause action
            pauseTask();
            // wait the connection for 5 minutes
            // Get the current time
            QDateTime startTime = QDateTime::currentDateTime();
            while(!isStop){
                QDateTime currentTime = QDateTime::currentDateTime();
                qint64 elapsedSeconds = startTime.secsTo(currentTime);
                if (elapsedSeconds >= 60) {
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
        sessions.push_back(s);
        return true;
    }else{
        // wait the connection for 5 minutes
        // Get the current time
        QDateTime startTime = QDateTime::currentDateTime();
        while(!isStop){
            QDateTime currentTime = QDateTime::currentDateTime();
            qint64 elapsedSeconds = startTime.secsTo(currentTime);
            if (elapsedSeconds >= 60) {
                // fail
                return false;
            }
            if(isConnect){
                return initiateSession();
            }
            QThread::msleep(1000);
        }
    }
}
bool MainWindow::doCalculate(){
    QThread::msleep(2000);
    return true;
    while(!isStop){

        newSessionMutex.lock();
        if (newSessionPaused) {
            newSessionPauseCondition.wait(&newSessionMutex);
        }
        newSessionMutex.unlock();

        cout<<"runing"<<endl;
        QThread::msleep(1000);

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
    pauseNewSessionTimer->setInterval(5000); // 5000 milliseconds = 5 seconds
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
    lightOff(ui->interface_blue);
    lightflashOff(ui->interface_red);
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
    // delete the session
    if (!sessions.empty()) {
        Session *newestSession = sessions.back();
        if(newestSession->getNeedDeleted()){
            delete sessions.back();
            sessions.pop_back();
        }
    }
    // close light
    lightflashOff(ui->interface_red);
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



/*
 * SESSION LOG
 */
void MainWindow::showMenuSelectionTwo(){
    bool flag = ui->interface_menu_selection1->isVisible();

    if(!flag){
        ui->interface_menu_selection1->setVisible(true);
        for (Session* s : sessions) {
            if(s != nullptr){
                QString date = QString::fromStdString(s->getDate());
                QString time = QString::fromStdString(s->getTime());
                QString itemText = date + " " + time;

                // Check if an item with the same text already exists
                QList<QListWidgetItem*> existingItems = ui->interface_menu_selection1->findItems(itemText, Qt::MatchExactly);
                if (existingItems.isEmpty()) {
                    // No existing item with the same text, so add a new item
                    QListWidgetItem *newItem = new QListWidgetItem();
                    newItem->setText(itemText);
                    ui->interface_menu_selection1->addItem(newItem);
                }
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
void MainWindow::lightflashOn(QGraphicsView* gv, const QString& color){
    if (gv) {
        // Store the original and flash colors in properties for later use
        gv->setProperty("originalColor", gv->styleSheet());
        gv->setProperty("flashColor", QString("QGraphicsView { background-color: %1; }").arg(color));

        // check
        disconnect(flashTimer, &QTimer::timeout, nullptr, nullptr);

        // Connect the timer's timeout signal to a lambda function that toggles the color
        connect(flashTimer, &QTimer::timeout, this, [gv]() {
            static bool flashState = false;
            if (flashState) {
                gv->setStyleSheet(gv->property("originalColor").toString());
            } else {
                gv->setStyleSheet(gv->property("flashColor").toString());
            }
            flashState = !flashState;
        });

        // Start the timer with an interval of 500 milliseconds (0.1 seconds)
        flashTimer->start(100);
    }
}
void MainWindow::lightflashOff(QGraphicsView* gv){
    if (gv) {
        if(flashTimer!=nullptr){
            flashTimer->stop();  // Stop the flashing timer
            QVariant originalColor = gv->property("originalColor");
            if (originalColor.isValid()) {
                gv->setStyleSheet(originalColor.toString());  // Restore the original color if it exists
            }
        }
    }
}


/*
 * BATTERY
 */
void MainWindow::batteryAction(){
    // duration is 33 minutes
    while(1){
        cout<<"battery: "<< batteryVolume<<endl;
        batteryMutex.lock();
        if (batteryPaused) {
            batteryPauseCondition.wait(&batteryMutex);
        }
        batteryMutex.unlock();


        // update value
        batteryVolume -= 0.5;
        // get value
        int currentValue = ui->interface_battery->value();
        int changedInt = static_cast<int>(batteryVolume);
        if(currentValue != changedInt){
            ui->interface_battery->setValue(changedInt);
        }
        if(!changedInt){
            AutoOff();
        }
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



/*
 * Utils
 *
*/
void MainWindow::power(){
    if(!batteryVolume){
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
 * EGG
 */
void MainWindow::toggleConnect(){
    isConnect = !isConnect;
}




// just for test
void MainWindow::test1(){
    toggleConnect();
    cout<<isConnect<<endl;
}

void MainWindow::test2(){
    int count = ui->interface_screen->children().count();
    cout<<count<<endl;
}



