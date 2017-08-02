#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T09:39:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = barscale
TEMPLATE    = app
DESTDIR     = $$PWD/../bin

SOURCES += main.cpp\
        frmbarscale.cpp \
    barscale.cpp \
    flatui.cpp

HEADERS  += frmbarscale.h \
    barscale.h \
    flatui.h

FORMS    += frmbarscale.ui
