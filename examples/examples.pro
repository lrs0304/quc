#-------------------------------------------------
#
# Project created by QtCreator 2016-12-17T11:38:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET              = examples
TEMPLATE            = app
MOC_DIR             = temp/moc
RCC_DIR             = temp/rcc
UI_DIR              = temp/ui
OBJECTS_DIR         = temp/obj
win32:RC_FILE       = main.rc
DESTDIR             = $$PWD/../bin
PRECOMPILED_HEADER  = head.h

RESOURCES           += main.qrc
CONFIG              += qt warn_off
INCLUDEPATH         += $$PWD/../designer/src
CONFIG(release, debug|release){
LIBS                += -L$$PWD/../bin/ -lquc
} else {
LIBS                += -L$$PWD/../bin/ -lqucd
}

SOURCES += \    
    main.cpp \
    frmmain.cpp \
    frmgaugespeed.cpp \
    frmgaugearc.cpp \
    frmgaugecar.cpp \
    frmgaugeclock.cpp \
    frmgaugecompass.cpp \
    frmgaugedial.cpp \
    frmgaugenet.cpp \
    frmgaugeprogressbar.cpp \
    frmgaugerange.cpp \
    frmgaugeround.cpp \
    frmgaugesimple.cpp \
    frmgaugewatch.cpp \
    frmimagecalendar.cpp \
    frmimageclock.cpp \
    frmimagepilot.cpp \
    frmimagepower.cpp \
    frmanimationbutton.cpp \
    frmbarruler.cpp \
    frmbarscale.cpp \
    frmbartemp.cpp \
    frmbarvolume.cpp \
    frmbattery.cpp \
    frmcpumemorylabel.cpp \
    frmcurvechart.cpp \
    frmdatetimelcd.cpp \
    frmdevicesizetable.cpp \
    frmimageview.cpp \
    frmlcdnumber.cpp \
    frmlednumber.cpp \
    frmledtext.cpp \
    frmlightbutton.cpp \
    frmnavlabel.cpp \
    frmnavlistview.cpp \
    frmnavlistviewform.cpp \
    frmnavprogressbar.cpp \
    frmbottomwidget.cpp \
    frmprogressbarcolor.cpp \
    frmprogressbarround.cpp \
    frmprogressbarwait.cpp \
    frmroundcircle.cpp \
    frmroundwidget.cpp \
    frmsliderbar.cpp \
    frmsliderbarform.cpp \
    frmsliderrange.cpp \
    frmsliderruler.cpp \
    frmswitchbutton.cpp \
    frmtextmovewidget.cpp \
    frmtumbler.cpp \
    frmlineruler.cpp \
    frmwavebar.cpp \
    frmwavedouble.cpp \
    frmwaveline.cpp \
    frmverifiedcode.cpp \
    frmpanelmovewidget.cpp \
    frmpanelwidget.cpp \
    frmpanelwidgetx.cpp \
    frmflatui.cpp \
    frmadswidget.cpp \
    frmprogressbarpercent.cpp \
    frmwaveplot.cpp \
    frmiconeditor.cpp \
    frmcombobox.cpp

HEADERS  += \
    frmmain.h \
    frmgaugespeed.h \
    frmgaugearc.h \
    frmgaugecar.h \
    frmgaugeclock.h \
    frmgaugecompass.h \
    frmgaugedial.h \
    frmgaugenet.h \
    frmgaugeprogressbar.h \
    frmgaugerange.h \
    frmgaugeround.h \
    frmgaugesimple.h \
    frmgaugewatch.h \
    frmimagecalendar.h \
    frmimageclock.h \
    frmimagepilot.h \
    frmimagepower.h \
    frmanimationbutton.h \
    frmbarruler.h \
    frmbarscale.h \
    frmbartemp.h \
    frmbarvolume.h \
    frmbattery.h \
    frmcpumemorylabel.h \
    frmcurvechart.h \
    frmdatetimelcd.h \
    frmdevicesizetable.h \
    frmimageview.h \
    frmlcdnumber.h \
    frmlednumber.h \
    frmledtext.h \
    frmlightbutton.h \
    frmnavlabel.h \
    frmnavlistview.h \
    frmnavlistviewform.h \
    frmnavprogressbar.h \
    frmbottomwidget.h \
    frmprogressbarcolor.h \
    frmprogressbarround.h \
    frmprogressbarwait.h \
    frmroundcircle.h \
    frmroundwidget.h \
    frmsliderbar.h \
    frmsliderbarform.h \
    frmsliderrange.h \
    frmsliderruler.h \
    frmswitchbutton.h \
    frmtextmovewidget.h \
    frmtumbler.h \
    frmlineruler.h \
    frmwavebar.h \
    frmwavedouble.h \
    frmwaveline.h \
    frmverifiedcode.h \
    frmpanelmovewidget.h \
    frmpanelwidget.h \
    frmpanelwidgetx.h \
    frmflatui.h \
    frmadswidget.h \
    frmprogressbarpercent.h \
    frmwaveplot.h \
    frmiconeditor.h \
    frmcombobox.h

FORMS    += \
    frmmain.ui \
    frmgaugespeed.ui \
    frmgaugearc.ui \
    frmgaugecar.ui \
    frmgaugeclock.ui \
    frmgaugecompass.ui \
    frmgaugedial.ui \
    frmgaugenet.ui \
    frmgaugeprogressbar.ui \
    frmgaugerange.ui \
    frmgaugeround.ui \
    frmgaugesimple.ui \
    frmgaugewatch.ui \
    frmimagecalendar.ui \
    frmimageclock.ui \
    frmimagepilot.ui \
    frmimagepower.ui \
    frmanimationbutton.ui \
    frmbarruler.ui \
    frmbarscale.ui \
    frmbartemp.ui \
    frmbarvolume.ui \
    frmbattery.ui \
    frmcpumemorylabel.ui \
    frmcurvechart.ui \
    frmdatetimelcd.ui \
    frmdevicesizetable.ui \
    frmimageview.ui \
    frmlcdnumber.ui \
    frmlednumber.ui \
    frmledtext.ui \
    frmlightbutton.ui \
    frmnavlabel.ui \
    frmnavlistview.ui \
    frmnavlistviewform.ui \
    frmnavprogressbar.ui \
    frmbottomwidget.ui \
    frmprogressbarcolor.ui \
    frmprogressbarround.ui \
    frmprogressbarwait.ui \
    frmroundcircle.ui \
    frmroundwidget.ui \
    frmsliderbar.ui \
    frmsliderbarform.ui \
    frmsliderrange.ui \
    frmsliderruler.ui \
    frmswitchbutton.ui \
    frmtextmovewidget.ui \
    frmtumbler.ui \
    frmlineruler.ui \
    frmwavebar.ui \
    frmwavedouble.ui \
    frmwaveline.ui \
    frmverifiedcode.ui \
    frmpanelmovewidget.ui \
    frmpanelwidget.ui \
    frmpanelwidgetx.ui \
    frmflatui.ui \
    frmadswidget.ui \
    frmprogressbarpercent.ui \
    frmwaveplot.ui \
    frmiconeditor.ui \
    frmcombobox.ui
