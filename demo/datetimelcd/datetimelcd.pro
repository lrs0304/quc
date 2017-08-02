#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T09:59:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = datetimelcd
TEMPLATE    = app
DESTDIR     = $$PWD/../bin

SOURCES += main.cpp\
        frmdatetimelcd.cpp \
    datetimelcd.cpp

HEADERS  += frmdatetimelcd.h \
    datetimelcd.h

FORMS    += frmdatetimelcd.ui
