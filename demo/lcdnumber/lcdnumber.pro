#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T14:48:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = lcdnumber
TEMPLATE    = app
DESTDIR     = $$PWD/../bin

SOURCES += main.cpp\
        frmlcdnumber.cpp \
    lcdnumber.cpp

HEADERS  += frmlcdnumber.h \
    lcdnumber.h

FORMS    += frmlcdnumber.ui
