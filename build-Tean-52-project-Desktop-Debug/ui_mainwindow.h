/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QFrame *interface_frame;
    QProgressBar *interface_battery;
    QFrame *interface_screen;
    QListWidget *interface_menu_selection;
    QTimeEdit *interface_menu_selection0_time;
    QProgressBar *interface_menu_selection0_progress;
    QListWidget *interface_menu_selection1;
    QFrame *interface_menu_selection0_completed;
    QLineEdit *lineEdit;
    QPushButton *completed_exit;
    QFrame *interface_menu_selection2_frame;
    QComboBox *interface_menu_selection2_combo;
    QTimeEdit *interface_menu_selection2_time;
    QDateEdit *interface_menu_selection2_date;
    QPushButton *interface_menu_selection2_increase;
    QPushButton *interface_menu_selection2_decrease;
    QPushButton *interface_menu;
    QPushButton *interface_power;
    QPushButton *interface_pause;
    QPushButton *interface_start;
    QPushButton *interface_stop;
    QGraphicsView *interface_blue;
    QGraphicsView *interface_green;
    QGraphicsView *interface_red;
    QPushButton *interface_recharge;
    QFrame *eeg_frame;
    QLabel *label;
    QPushButton *toggleConnection;
    QFrame *pc_transation;
    QLabel *label_2;
    QPushButton *pc_submit;
    QFrame *pc_screen;
    QLabel *label_3;
    QLabel *after_baseline_freq;
    QListWidget *pc_monitor_show;
    QWidget *waveform_box;
    QLabel *label_4;
    QFrame *line;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1289, 834);
        QFont font;
        font.setPointSize(9);
        MainWindow->setFont(font);
        MainWindow->setToolButtonStyle(Qt::ToolButtonIconOnly);
        MainWindow->setTabShape(QTabWidget::Rounded);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        interface_frame = new QFrame(centralwidget);
        interface_frame->setObjectName(QString::fromUtf8("interface_frame"));
        interface_frame->setGeometry(QRect(290, 20, 350, 400));
        interface_frame->setStyleSheet(QString::fromUtf8("QFrame { background-color: white; }"));
        interface_frame->setFrameShape(QFrame::StyledPanel);
        interface_frame->setFrameShadow(QFrame::Raised);
        interface_battery = new QProgressBar(interface_frame);
        interface_battery->setObjectName(QString::fromUtf8("interface_battery"));
        interface_battery->setGeometry(QRect(310, 350, 20, 40));
        interface_battery->setStyleSheet(QString::fromUtf8(""));
        interface_battery->setValue(100);
        interface_battery->setAlignment(Qt::AlignCenter);
        interface_battery->setTextVisible(false);
        interface_battery->setOrientation(Qt::Vertical);
        interface_screen = new QFrame(interface_frame);
        interface_screen->setObjectName(QString::fromUtf8("interface_screen"));
        interface_screen->setGeometry(QRect(60, 100, 191, 151));
        interface_screen->setFrameShape(QFrame::StyledPanel);
        interface_screen->setFrameShadow(QFrame::Raised);
        interface_menu_selection = new QListWidget(interface_screen);
        QFont font1;
        font1.setPointSize(12);
        QListWidgetItem *__qlistwidgetitem = new QListWidgetItem(interface_menu_selection);
        __qlistwidgetitem->setFont(font1);
        QListWidgetItem *__qlistwidgetitem1 = new QListWidgetItem(interface_menu_selection);
        __qlistwidgetitem1->setFont(font1);
        QListWidgetItem *__qlistwidgetitem2 = new QListWidgetItem(interface_menu_selection);
        __qlistwidgetitem2->setFont(font1);
        interface_menu_selection->setObjectName(QString::fromUtf8("interface_menu_selection"));
        interface_menu_selection->setGeometry(QRect(30, 30, 141, 101));
        interface_menu_selection->setStyleSheet(QString::fromUtf8("QListWidget { background-color: transparent; }"));
        interface_menu_selection0_time = new QTimeEdit(interface_screen);
        interface_menu_selection0_time->setObjectName(QString::fromUtf8("interface_menu_selection0_time"));
        interface_menu_selection0_time->setGeometry(QRect(40, 30, 111, 61));
        QFont font2;
        font2.setPointSize(30);
        font2.setBold(true);
        font2.setWeight(75);
        interface_menu_selection0_time->setFont(font2);
        interface_menu_selection0_time->setStyleSheet(QString::fromUtf8("QTimeEdit {\n"
"                border: none;\n"
"                background: transparent;\n"
"            }\n"
"QTimeEdit::up-button, QTimeEdit::down-button {\n"
"    subcontrol-origin: padding;\n"
"    subcontrol-position: top right;\n"
"    width: 0px;\n"
"}\n"
"QTimeEdit::up-arrow, QTimeEdit::down-arrow {\n"
"    image: none;\n"
"}"));
        interface_menu_selection0_progress = new QProgressBar(interface_screen);
        interface_menu_selection0_progress->setObjectName(QString::fromUtf8("interface_menu_selection0_progress"));
        interface_menu_selection0_progress->setGeometry(QRect(20, 110, 150, 15));
        interface_menu_selection0_progress->setValue(0);
        interface_menu_selection1 = new QListWidget(interface_screen);
        interface_menu_selection1->setObjectName(QString::fromUtf8("interface_menu_selection1"));
        interface_menu_selection1->setGeometry(QRect(10, 10, 170, 130));
        interface_menu_selection1->setFont(font1);
        interface_menu_selection0_completed = new QFrame(interface_screen);
        interface_menu_selection0_completed->setObjectName(QString::fromUtf8("interface_menu_selection0_completed"));
        interface_menu_selection0_completed->setGeometry(QRect(40, 30, 120, 80));
        interface_menu_selection0_completed->setFrameShape(QFrame::StyledPanel);
        interface_menu_selection0_completed->setFrameShadow(QFrame::Raised);
        lineEdit = new QLineEdit(interface_menu_selection0_completed);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(10, 20, 100, 23));
        lineEdit->setFont(font1);
        lineEdit->setFrame(false);
        completed_exit = new QPushButton(interface_menu_selection0_completed);
        completed_exit->setObjectName(QString::fromUtf8("completed_exit"));
        completed_exit->setGeometry(QRect(40, 50, 40, 23));
        interface_menu_selection2_frame = new QFrame(interface_screen);
        interface_menu_selection2_frame->setObjectName(QString::fromUtf8("interface_menu_selection2_frame"));
        interface_menu_selection2_frame->setGeometry(QRect(10, 10, 170, 130));
        interface_menu_selection2_frame->setStyleSheet(QString::fromUtf8("QFrame { background-color: white; }"));
        interface_menu_selection2_frame->setFrameShape(QFrame::StyledPanel);
        interface_menu_selection2_frame->setFrameShadow(QFrame::Raised);
        interface_menu_selection2_combo = new QComboBox(interface_menu_selection2_frame);
        interface_menu_selection2_combo->addItem(QString());
        interface_menu_selection2_combo->addItem(QString());
        interface_menu_selection2_combo->addItem(QString());
        interface_menu_selection2_combo->addItem(QString());
        interface_menu_selection2_combo->addItem(QString());
        interface_menu_selection2_combo->addItem(QString());
        interface_menu_selection2_combo->setObjectName(QString::fromUtf8("interface_menu_selection2_combo"));
        interface_menu_selection2_combo->setGeometry(QRect(40, 70, 71, 23));
        interface_menu_selection2_time = new QTimeEdit(interface_menu_selection2_frame);
        interface_menu_selection2_time->setObjectName(QString::fromUtf8("interface_menu_selection2_time"));
        interface_menu_selection2_time->setGeometry(QRect(30, 40, 101, 24));
        QFont font3;
        font3.setPointSize(15);
        interface_menu_selection2_time->setFont(font3);
        interface_menu_selection2_time->setStyleSheet(QString::fromUtf8("QTimeEdit {\n"
"                border: none;\n"
"                background: transparent;\n"
"            }\n"
"QTimeEdit::up-button, QTimeEdit::down-button {\n"
"    subcontrol-origin: padding;\n"
"    subcontrol-position: top right;\n"
"    width: 0px;\n"
"}\n"
"QTimeEdit::up-arrow, QTimeEdit::down-arrow {\n"
"    image: none;\n"
"}"));
        interface_menu_selection2_date = new QDateEdit(interface_menu_selection2_frame);
        interface_menu_selection2_date->setObjectName(QString::fromUtf8("interface_menu_selection2_date"));
        interface_menu_selection2_date->setGeometry(QRect(20, 10, 121, 24));
        interface_menu_selection2_date->setFont(font3);
        interface_menu_selection2_date->setStyleSheet(QString::fromUtf8("QDateEdit {\n"
"                border: none;\n"
"                background: transparent;\n"
"            }\n"
"QDateEdit::up-button, QDateEdit::down-button {\n"
"    subcontrol-origin: padding;\n"
"    subcontrol-position: top right;\n"
"    width: 0px;\n"
"}\n"
"QDateEdit::up-arrow, QDatedit::down-arrow {\n"
"    image: none;\n"
"}"));
        interface_menu_selection2_increase = new QPushButton(interface_menu_selection2_frame);
        interface_menu_selection2_increase->setObjectName(QString::fromUtf8("interface_menu_selection2_increase"));
        interface_menu_selection2_increase->setGeometry(QRect(20, 100, 40, 23));
        interface_menu_selection2_decrease = new QPushButton(interface_menu_selection2_frame);
        interface_menu_selection2_decrease->setObjectName(QString::fromUtf8("interface_menu_selection2_decrease"));
        interface_menu_selection2_decrease->setGeometry(QRect(100, 100, 40, 23));
        interface_menu = new QPushButton(interface_frame);
        interface_menu->setObjectName(QString::fromUtf8("interface_menu"));
        interface_menu->setGeometry(QRect(60, 70, 51, 23));
        interface_power = new QPushButton(interface_frame);
        interface_power->setObjectName(QString::fromUtf8("interface_power"));
        interface_power->setGeometry(QRect(280, 10, 61, 23));
        interface_pause = new QPushButton(interface_frame);
        interface_pause->setObjectName(QString::fromUtf8("interface_pause"));
        interface_pause->setGeometry(QRect(60, 270, 50, 23));
        interface_start = new QPushButton(interface_frame);
        interface_start->setObjectName(QString::fromUtf8("interface_start"));
        interface_start->setGeometry(QRect(130, 270, 50, 23));
        interface_stop = new QPushButton(interface_frame);
        interface_stop->setObjectName(QString::fromUtf8("interface_stop"));
        interface_stop->setGeometry(QRect(200, 270, 50, 23));
        interface_blue = new QGraphicsView(interface_frame);
        interface_blue->setObjectName(QString::fromUtf8("interface_blue"));
        interface_blue->setGeometry(QRect(10, 10, 15, 30));
        interface_blue->setStyleSheet(QString::fromUtf8("QGraphicsView{background-color:grey;}"));
        interface_green = new QGraphicsView(interface_frame);
        interface_green->setObjectName(QString::fromUtf8("interface_green"));
        interface_green->setGeometry(QRect(30, 10, 15, 30));
        interface_green->setStyleSheet(QString::fromUtf8("QGraphicsView{background-color:grey;}"));
        interface_red = new QGraphicsView(interface_frame);
        interface_red->setObjectName(QString::fromUtf8("interface_red"));
        interface_red->setGeometry(QRect(50, 10, 15, 30));
        interface_red->setStyleSheet(QString::fromUtf8("QGraphicsView{background-color:grey;}"));
        interface_recharge = new QPushButton(interface_frame);
        interface_recharge->setObjectName(QString::fromUtf8("interface_recharge"));
        interface_recharge->setGeometry(QRect(220, 360, 80, 23));
        eeg_frame = new QFrame(centralwidget);
        eeg_frame->setObjectName(QString::fromUtf8("eeg_frame"));
        eeg_frame->setGeometry(QRect(30, 170, 191, 111));
        eeg_frame->setStyleSheet(QString::fromUtf8("QFrame { background-color: white; }"));
        eeg_frame->setFrameShape(QFrame::StyledPanel);
        eeg_frame->setFrameShadow(QFrame::Raised);
        label = new QLabel(eeg_frame);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 30, 131, 16));
        label->setFont(font1);
        toggleConnection = new QPushButton(eeg_frame);
        toggleConnection->setObjectName(QString::fromUtf8("toggleConnection"));
        toggleConnection->setGeometry(QRect(50, 70, 80, 23));
        toggleConnection->setCheckable(true);
        toggleConnection->setChecked(false);
        pc_transation = new QFrame(centralwidget);
        pc_transation->setObjectName(QString::fromUtf8("pc_transation"));
        pc_transation->setGeometry(QRect(690, 160, 191, 111));
        pc_transation->setStyleSheet(QString::fromUtf8("QFrame { background-color: white; }"));
        pc_transation->setFrameShape(QFrame::StyledPanel);
        pc_transation->setFrameShadow(QFrame::Raised);
        label_2 = new QLabel(pc_transation);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(40, 30, 131, 16));
        label_2->setFont(font1);
        pc_submit = new QPushButton(pc_transation);
        pc_submit->setObjectName(QString::fromUtf8("pc_submit"));
        pc_submit->setGeometry(QRect(50, 70, 80, 23));
        pc_screen = new QFrame(centralwidget);
        pc_screen->setObjectName(QString::fromUtf8("pc_screen"));
        pc_screen->setGeometry(QRect(220, 430, 291, 231));
        pc_screen->setStyleSheet(QString::fromUtf8("QFrame { background-color: white; }"));
        pc_screen->setFrameShape(QFrame::StyledPanel);
        pc_screen->setFrameShadow(QFrame::Raised);
        label_3 = new QLabel(pc_screen);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 10, 131, 16));
        label_3->setFont(font1);
        after_baseline_freq = new QLabel(pc_screen);
        after_baseline_freq->setObjectName(QString::fromUtf8("after_baseline_freq"));
        after_baseline_freq->setGeometry(QRect(20, 260, 631, 61));
        pc_monitor_show = new QListWidget(pc_screen);
        pc_monitor_show->setObjectName(QString::fromUtf8("pc_monitor_show"));
        pc_monitor_show->setGeometry(QRect(30, 40, 231, 130));
        pc_monitor_show->setFont(font1);
        waveform_box = new QWidget(centralwidget);
        waveform_box->setObjectName(QString::fromUtf8("waveform_box"));
        waveform_box->setGeometry(QRect(600, 480, 441, 171));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(610, 450, 201, 31));
        QFont font4;
        font4.setFamily(QString::fromUtf8("DejaVu Sans"));
        font4.setPointSize(12);
        label_4->setFont(font4);
        line = new QFrame(centralwidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(580, 490, 20, 141));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(570, 510, 21, 17));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(570, 530, 21, 17));
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(570, 550, 21, 17));
        label_8 = new QLabel(centralwidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(570, 570, 21, 17));
        label_9 = new QLabel(centralwidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(580, 590, 21, 17));
        label_10 = new QLabel(centralwidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(580, 610, 21, 17));
        label_11 = new QLabel(centralwidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(570, 490, 21, 17));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1289, 20));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));

        const bool __sortingEnabled = interface_menu_selection->isSortingEnabled();
        interface_menu_selection->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = interface_menu_selection->item(0);
        ___qlistwidgetitem->setText(QCoreApplication::translate("MainWindow", "NEW SESSION", nullptr));
        QListWidgetItem *___qlistwidgetitem1 = interface_menu_selection->item(1);
        ___qlistwidgetitem1->setText(QCoreApplication::translate("MainWindow", "SESSION LOG", nullptr));
        QListWidgetItem *___qlistwidgetitem2 = interface_menu_selection->item(2);
        ___qlistwidgetitem2->setText(QCoreApplication::translate("MainWindow", "TIME AND DATE", nullptr));
        interface_menu_selection->setSortingEnabled(__sortingEnabled);

        interface_menu_selection0_time->setDisplayFormat(QCoreApplication::translate("MainWindow", "m:ss", nullptr));
        lineEdit->setText(QCoreApplication::translate("MainWindow", "Completed!", nullptr));
        completed_exit->setText(QCoreApplication::translate("MainWindow", "EXIT", nullptr));
        interface_menu_selection2_combo->setItemText(0, QCoreApplication::translate("MainWindow", "Year", nullptr));
        interface_menu_selection2_combo->setItemText(1, QCoreApplication::translate("MainWindow", "Month", nullptr));
        interface_menu_selection2_combo->setItemText(2, QCoreApplication::translate("MainWindow", "Day", nullptr));
        interface_menu_selection2_combo->setItemText(3, QCoreApplication::translate("MainWindow", "Hour", nullptr));
        interface_menu_selection2_combo->setItemText(4, QCoreApplication::translate("MainWindow", "Minute", nullptr));
        interface_menu_selection2_combo->setItemText(5, QCoreApplication::translate("MainWindow", "Second", nullptr));

        interface_menu_selection2_time->setDisplayFormat(QCoreApplication::translate("MainWindow", "hh:mm:ss", nullptr));
        interface_menu_selection2_date->setDisplayFormat(QCoreApplication::translate("MainWindow", "yyyy-MM-dd", nullptr));
        interface_menu_selection2_increase->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
        interface_menu_selection2_decrease->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        interface_menu->setText(QCoreApplication::translate("MainWindow", "Menu", nullptr));
        interface_power->setText(QCoreApplication::translate("MainWindow", "ON/OFF", nullptr));
        interface_pause->setText(QCoreApplication::translate("MainWindow", "PAUSE", nullptr));
        interface_start->setText(QCoreApplication::translate("MainWindow", "START", nullptr));
        interface_stop->setText(QCoreApplication::translate("MainWindow", "STOP", nullptr));
        interface_recharge->setText(QCoreApplication::translate("MainWindow", "ReCharge", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "EEG Connection", nullptr));
        toggleConnection->setText(QCoreApplication::translate("MainWindow", "OFF", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "PC Transation", nullptr));
        pc_submit->setText(QCoreApplication::translate("MainWindow", "Submit", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "PC Moniotor", nullptr));
        after_baseline_freq->setText(QString());
        label_4->setText(QCoreApplication::translate("MainWindow", "EEG Waveform Graph", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "25", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "20", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "15", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "10", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "5", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "30", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
