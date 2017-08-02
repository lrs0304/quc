#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T10:52:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = gaugeround
TEMPLATE    = app
DESTDIR     = $$PWD/../bin

SOURCES += main.cpp\
        frmgaugeround.cpp \
    flatui.cpp \
    gaugeround.cpp

HEADERS  += frmgaugeround.h \
    flatui.h \
    gaugeround.h

FORMS    += frmgaugeround.ui
