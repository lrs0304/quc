#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T10:14:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = gaugecar
TEMPLATE    = app
DESTDIR     = $$PWD/../bin

SOURCES += main.cpp\
        frmgaugecar.cpp \
    flatui.cpp \
    gaugecar.cpp

HEADERS  += frmgaugecar.h \
    flatui.h \
    gaugecar.h

FORMS    += frmgaugecar.ui
