#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T16:19:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = sliderrange
TEMPLATE    = app
DESTDIR     = $$PWD/../bin

SOURCES += main.cpp\
        frmsliderrange.cpp \
    sliderrange.cpp

HEADERS  += frmsliderrange.h \
    sliderrange.h

FORMS    += frmsliderrange.ui
