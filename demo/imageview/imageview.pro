#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T14:43:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = imageview
TEMPLATE    = app
DESTDIR     = $$PWD/../bin

SOURCES += main.cpp\
        frmimageview.cpp \
    imageview.cpp

HEADERS  += frmimageview.h \
    imageview.h

FORMS    += frmimageview.ui

RESOURCES += \
    main.qrc
