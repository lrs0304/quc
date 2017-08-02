#-------------------------------------------------
#
# Project created by QtCreator 2016-12-16T16:18:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = gaugenet
TEMPLATE    = app
DESTDIR     = $$PWD/../bin

SOURCES += main.cpp\
        frmgaugenet.cpp \
    gaugenet.cpp \
    flatui.cpp

HEADERS  += frmgaugenet.h \
    gaugenet.h \
    flatui.h

FORMS    += frmgaugenet.ui

RESOURCES += \
    main.qrc
