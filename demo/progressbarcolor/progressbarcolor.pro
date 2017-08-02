#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T15:54:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = progressbarcolor
TEMPLATE    = app
DESTDIR     = $$PWD/../bin

SOURCES += main.cpp\
        frmprogressbarcolor.cpp \
    flatui.cpp \
    progressbarcolor.cpp

HEADERS  += frmprogressbarcolor.h \
    flatui.h \
    progressbarcolor.h

FORMS    += frmprogressbarcolor.ui
