#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T11:14:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = gaugewatch
TEMPLATE    = app
DESTDIR     = $$PWD/../bin

SOURCES += main.cpp\
        frmgaugewatch.cpp \
    flatui.cpp \
    gaugewatch.cpp

HEADERS  += frmgaugewatch.h \
    flatui.h \
    gaugewatch.h

FORMS    += frmgaugewatch.ui
