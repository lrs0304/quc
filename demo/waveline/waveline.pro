#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T16:46:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = waveline
TEMPLATE    = app
DESTDIR     = $$PWD/../bin

SOURCES += main.cpp\
        frmwaveline.cpp \
    waveline.cpp

HEADERS  += frmwaveline.h \
    waveline.h

FORMS    += frmwaveline.ui
