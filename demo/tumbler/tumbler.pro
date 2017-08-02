#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T16:37:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = tumbler
TEMPLATE    = app
DESTDIR     = $$PWD/../bin

SOURCES += main.cpp\
        frmtumbler.cpp \
    tumbler.cpp

HEADERS  += frmtumbler.h \
    tumbler.h

FORMS    += frmtumbler.ui
