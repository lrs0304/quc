#-------------------------------------------------
#
# Project created by QtCreator 2017-02-13T12:39:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = iconeditor
TEMPLATE    = app
DESTDIR     = $$PWD/../bin

SOURCES += main.cpp\
        frmiconeditor.cpp \
    iconeditor.cpp

HEADERS  += frmiconeditor.h \
    iconeditor.h

FORMS    += frmiconeditor.ui
