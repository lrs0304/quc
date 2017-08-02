#-------------------------------------------------
#
# Project created by QtCreator 2017-01-07T12:06:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = gaugearc
TEMPLATE    = app
DESTDIR     = $$PWD/../bin

SOURCES += main.cpp\
        frmgaugearc.cpp \
    gaugearc.cpp \
    flatui.cpp

HEADERS  += frmgaugearc.h \
    gaugearc.h \
    flatui.h

FORMS    += frmgaugearc.ui

RESOURCES += \
    main.qrc
