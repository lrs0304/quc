#-------------------------------------------------
#
# Project created by QtCreator 2017-01-12T10:09:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET 		= waveplot
TEMPLATE 	= app
DESTDIR     = $$PWD/../bin

SOURCES += main.cpp\
        frmwaveplot.cpp \
    waveplot.cpp \
    flatui.cpp

HEADERS  += frmwaveplot.h \
    waveplot.h \
    flatui.h

FORMS    += frmwaveplot.ui
