#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T10:55:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = gaugesimple
TEMPLATE    = app
DESTDIR     = $$PWD/../bin

SOURCES += main.cpp\
        frmgaugesimple.cpp \
    flatui.cpp \
    gaugesimple.cpp

HEADERS  += frmgaugesimple.h \
    flatui.h \
    gaugesimple.h

FORMS    += frmgaugesimple.ui
