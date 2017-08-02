#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T15:15:36
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = navlistview
TEMPLATE    = app
DESTDIR     = $$PWD/../bin

SOURCES += main.cpp\
        frmnavlistview.cpp \
    navlistview.cpp \
    frmnavlistviewform.cpp

HEADERS  += frmnavlistview.h \
    navlistview.h \
    frmnavlistviewform.h

FORMS    += frmnavlistview.ui \
    frmnavlistviewform.ui

RESOURCES += \
    main.qrc
