#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T11:38:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = imageclock
TEMPLATE    = app
DESTDIR     = $$PWD/../bin

SOURCES += main.cpp\
        frmimageclock.cpp \
    imageclock.cpp

HEADERS  += frmimageclock.h \
    imageclock.h

FORMS    += frmimageclock.ui

RESOURCES += \
    main.qrc
