#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T16:15:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = sliderbar
TEMPLATE    = app
DESTDIR     = $$PWD/../bin

SOURCES += main.cpp\
        frmsliderbar.cpp \
    frmsliderbarform.cpp \
    sliderbar.cpp

HEADERS  += frmsliderbar.h \
    frmsliderbarform.h \
    sliderbar.h

FORMS    += frmsliderbar.ui \
    frmsliderbarform.ui
