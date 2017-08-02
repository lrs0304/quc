#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T10:49:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = gaugerange
TEMPLATE    = app
DESTDIR     = $$PWD/../bin

SOURCES += main.cpp\
        frmgaugerange.cpp \
    flatui.cpp \
    gaugerange.cpp

HEADERS  += frmgaugerange.h \
    flatui.h \
    gaugerange.h

FORMS    += frmgaugerange.ui

RESOURCES += \
    main.qrc
