#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T16:42:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = wavebar
TEMPLATE    = app
DESTDIR     = $$PWD/../bin

SOURCES += main.cpp\
        frmwavebar.cpp \
    wavebar.cpp

HEADERS  += frmwavebar.h \
    wavebar.h

FORMS    += frmwavebar.ui
