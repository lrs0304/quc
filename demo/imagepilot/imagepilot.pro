#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T14:36:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = imagepilot
TEMPLATE    = app
DESTDIR     = $$PWD/../bin

SOURCES += main.cpp\
        frmimagepilot.cpp \
    imagepilot.cpp

HEADERS  += frmimagepilot.h \
    imagepilot.h

FORMS    += frmimagepilot.ui

RESOURCES += \
    main.qrc
