#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T10:37:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = gaugeprogressbar
TEMPLATE    = app
DESTDIR     = $$PWD/../bin

SOURCES += main.cpp\
        frmgaugeprogressbar.cpp \
    flatui.cpp \
    gaugeprogressbar.cpp

HEADERS  += frmgaugeprogressbar.h \
    flatui.h \
    gaugeprogressbar.h

FORMS    += frmgaugeprogressbar.ui
