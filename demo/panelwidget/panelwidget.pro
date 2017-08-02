#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T15:50:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = panelwidget
TEMPLATE    = app
DESTDIR     = $$PWD/../bin

SOURCES += main.cpp\
        frmpanelwidget.cpp \
    frmpanelwidgetx.cpp \
    gaugeprogressbar.cpp \
    lightbutton.cpp \
    panelwidget.cpp

HEADERS  += frmpanelwidget.h \
    frmpanelwidgetx.h \
    gaugeprogressbar.h \
    lightbutton.h \
    panelwidget.h

FORMS    += frmpanelwidget.ui \
    frmpanelwidgetx.ui

DISTFILES +=
