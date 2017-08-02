#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T15:59:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = progressbarround
TEMPLATE    = app
DESTDIR     = $$PWD/../bin

SOURCES += main.cpp\
        frmprogressbarround.cpp \
    flatui.cpp \
    progressbarround.cpp

HEADERS  += frmprogressbarround.h \
    flatui.h \
    progressbarround.h

FORMS    += frmprogressbarround.ui
