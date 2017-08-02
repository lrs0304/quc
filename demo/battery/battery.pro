#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T09:46:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = battery
TEMPLATE    = app
DESTDIR     = $$PWD/../bin

SOURCES += main.cpp\
        frmbattery.cpp \
    battery.cpp \
    flatui.cpp

HEADERS  += frmbattery.h \
    battery.h \
    flatui.h

FORMS    += frmbattery.ui
