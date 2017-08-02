#-------------------------------------------------
#
# Project created by QtCreator 2017-01-05T22:11:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = barvolume
TEMPLATE    = app
DESTDIR     = $$PWD/../bin

SOURCES += main.cpp\
        frmbarvolume.cpp \
    barvolume.cpp

HEADERS  += frmbarvolume.h \
    barvolume.h

FORMS    += frmbarvolume.ui
