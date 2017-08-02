greaterThan(QT_MAJOR_VERSION, 4) {
    QT += designer
} else {
    QT += xml
    CONFIG += designer
}

target.path         = $$[QT_INSTALL_PLUGINS]/designer
TARGET              = $$qtLibraryTarget(quc)
TEMPLATE            = lib
RESOURCES           = main.qrc

INSTALLS            += target
CONFIG              += qt plugin warn_off
DEFINES             += quc
LIBS                += -L.

MOC_DIR             = temp/moc
RCC_DIR             = temp/rcc
UI_DIR              = temp/ui
OBJECTS_DIR         = temp/obj
DESTDIR             = $$PWD/../bin
PRECOMPILED_HEADER  = head.h

include(src/src.pri)
include(plugin/plugin.pri)

win32 {
    src_file = $$PWD/../bin/quc.dll
    dst_file = $(QTDIR)/plugins/designer
    src_file ~= s,/,\\,g
    dst_file ~= s,/,\\,g
    QMAKE_POST_LINK += copy $$src_file $$dst_file
}
unix {
    src_file = $$PWD/../bin/libquc.so
    dst_file = $(QTDIR)/plugins/designer
    QMAKE_POST_LINK += cp -r -f $$src_file $$dst_file
}
