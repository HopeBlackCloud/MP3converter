#-------------------------------------------------
#
# Project created by QtCreator 2018-06-11T23:07:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MP3EncoderGUI
TEMPLATE = app

INCLUDEPATH += ../cots/lame-3.100/include \
               ../../common/include

LIBS += -L/usr/local/lib -lmp3lame

SOURCES += src/main.cpp\
        src/Mainwindow.cpp \
    ../../../common/src/EasyLame.cpp \
    ../../../common/src/EncoderController.cpp \
    ../../../common/src/EncoderThread.cpp \
    ../../../common/src/MP3Info.cpp \
    ../../../common/src/Utility.cpp \
    ../../../common/src/WAVInfo.cpp


HEADERS  += src/Mainwindow.h \
    ../../../common/include/Definitions.h \
    ../../../common/include/EasyLame.h \
    ../../../common/include/EncoderController.h \
    ../../../common/include/EncoderThread.h \
    ../../../common/include/MP3Info.h \
    ../../../common/include/Utility.h \
    ../../../common/include/WavFileException.h \
    ../../../common/include/WAVInfo.h \
    ../../../common/include/WorkerThread.h

FORMS    += src/Mainwindow.ui
