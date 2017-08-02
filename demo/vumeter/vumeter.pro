#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T09:32:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = barruler
TEMPLATE    = app
DESTDIR     = $$PWD/../bin

SOURCES += main.cpp\
    frmvumeter.cpp \
    vumeter.cpp

FORMS += \
    frmvumeter.ui

HEADERS += \
    frmvumeter.h \
    vumeter.h

