#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T14:39:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = imagepower
TEMPLATE    = app
DESTDIR     = $$PWD/../bin

SOURCES += main.cpp\
        frmimagepower.cpp \
    imagepower.cpp

HEADERS  += frmimagepower.h \
    imagepower.h

FORMS    += frmimagepower.ui

RESOURCES += \
    main.qrc
