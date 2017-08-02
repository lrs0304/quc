#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T11:05:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = gaugespeed
TEMPLATE    = app
DESTDIR     = $$PWD/../bin

SOURCES += main.cpp\
        frmgaugespeed.cpp \
    flatui.cpp \
    gaugespeed.cpp

HEADERS  += frmgaugespeed.h \
    flatui.h \
    gaugespeed.h

FORMS    += frmgaugespeed.ui

RESOURCES += \
    main.qrc
