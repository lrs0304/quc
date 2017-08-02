#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T10:22:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = gaugedial
TEMPLATE    = app
DESTDIR     = $$PWD/../bin

SOURCES += main.cpp\
        frmgaugedial.cpp \
    flatui.cpp \
    gaugedial.cpp

HEADERS  += frmgaugedial.h \
    flatui.h \
    gaugedial.h

FORMS    += frmgaugedial.ui
