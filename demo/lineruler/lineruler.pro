#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T15:08:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = lineruler
TEMPLATE    = app
DESTDIR     = $$PWD/../bin

SOURCES += main.cpp\
        frmlineruler.cpp \
    flatui.cpp \
    lineruler.cpp

HEADERS  += frmlineruler.h \
    flatui.h \
    lineruler.h

FORMS    += frmlineruler.ui
