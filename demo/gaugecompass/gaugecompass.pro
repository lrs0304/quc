#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T10:19:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = gaugecompass
TEMPLATE    = app
DESTDIR     = $$PWD/../bin

SOURCES += main.cpp\
        frmgaugecompass.cpp \
    flatui.cpp \
    gaugecompass.cpp

HEADERS  += frmgaugecompass.h \
    flatui.h \
    gaugecompass.h

FORMS    += frmgaugecompass.ui
