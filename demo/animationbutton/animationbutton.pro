#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T09:24:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = animationbutton
TEMPLATE    = app
DESTDIR     = $$PWD/../bin

SOURCES += main.cpp\
        frmanimationbutton.cpp \
    animationbutton1.cpp \
    animationbutton2.cpp

HEADERS  += frmanimationbutton.h \
    animationbutton1.h \
    animationbutton2.h

FORMS    += frmanimationbutton.ui

RESOURCES += \
    main.qrc
