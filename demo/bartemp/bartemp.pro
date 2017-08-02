#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T09:44:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = bartemp
TEMPLATE    = app
DESTDIR     = $$PWD/../bin

SOURCES += main.cpp\
        frmbartemp.cpp \
    bartemp.cpp

HEADERS  += frmbartemp.h \
    bartemp.h

FORMS    += frmbartemp.ui
