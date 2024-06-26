QT       += core gui
QT += multimedia   #'sudo apt-get install qtmultimedia5-dev' download the library
QT += concurrent   #for multi-thread

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    analysisWave.cpp \
    main.cpp \
    mainwindow.cpp \
    session.cpp \
    site.cpp \
    waveSimulator.cpp

HEADERS += \
    analysisWave.h \
    frequencyBands.h \
    mainwindow.h \
    session.h \
    site.h \
    waveSimulator.h

FORMS += \
    mainwindow.ui


RESOURCES += /home/student/Downloads/beep.qrc # `wget https://www.soundjay.com/buttons/beep-01a.wav` download the sound



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
