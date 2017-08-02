#-------------------------------------------------
#
# Project created by QtCreator 2017-01-07T17:11:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = progressbarpercent
TEMPLATE    = app
DESTDIR     = $$PWD/../bin

SOURCES += main.cpp\
        frmprogressbarpercent.cpp \
    progressbarpercent.cpp \
    flatui.cpp

HEADERS  += frmprogressbarpercent.h \
    progressbarpercent.h \
    flatui.h

FORMS    += frmprogressbarpercent.ui
