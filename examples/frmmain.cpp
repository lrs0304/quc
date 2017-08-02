#pragma execution_character_set("utf-8")

#include "frmmain.h"
#include "ui_frmmain.h"

#include "frmgaugearc.h"
#include "frmgaugecar.h"
#include "frmgaugeclock.h"
#include "frmgaugecompass.h"
#include "frmgaugedial.h"
#include "frmgaugenet.h"
#include "frmgaugeprogressbar.h"
#include "frmgaugerange.h"
#include "frmgaugeround.h"
#include "frmgaugesimple.h"
#include "frmgaugespeed.h"
#include "frmgaugewatch.h"

#include "frmimagecalendar.h"
#include "frmimageclock.h"
#include "frmimagepilot.h"
#include "frmimagepower.h"
#include "frmimageview.h"

#include "frmanimationbutton.h"
#include "frmbarruler.h"
#include "frmbarscale.h"
#include "frmbartemp.h"
#include "frmbarvolume.h"
#include "frmbattery.h"

#include "frmcpumemorylabel.h"
#include "frmcurvechart.h"
#include "frmdatetimelcd.h"
#include "frmdevicesizetable.h"

#include "frmlcdnumber.h"
#include "frmlednumber.h"
#include "frmledtext.h"
#include "frmlightbutton.h"

#include "frmnavlabel.h"
#include "frmnavlistview.h"
#include "frmnavlistviewform.h"
#include "frmnavprogressbar.h"

#include "frmbottomwidget.h"
#include "frmprogressbarcolor.h"
#include "frmprogressbarpercent.h"
#include "frmprogressbarround.h"
#include "frmprogressbarwait.h"

#include "frmroundcircle.h"
#include "frmroundwidget.h"
#include "frmsliderbar.h"
#include "frmsliderbarform.h"
#include "frmsliderrange.h"
#include "frmsliderruler.h"
#include "frmlineruler.h"

#include "frmtumbler.h"
#include "frmswitchbutton.h"
#include "frmtextmovewidget.h"
#include "frmverifiedcode.h"

#include "frmwavebar.h"
#include "frmwavedouble.h"
#include "frmwaveline.h"
#include "frmwaveplot.h"
#include "frmpanelmovewidget.h"
#include "frmpanelwidget.h"
#include "frmflatui.h"
#include "frmadswidget.h"
#include "frmiconeditor.h"
#include "frmcombobox.h"

#include "screenwidget.h"
#include "colorwidget.h"
#include "maskwidget.h"
#include "trayicon.h"
#include "lunarcalendarinfo.h"

#include "qdebug.h"
#include "qdialog.h"
#include "qdesktopwidget.h"

frmMain::frmMain(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmMain)
{
    ui->setupUi(this);
    this->initForm();

    //居中显示窗体
    int frmX = this->width();
    int frmY = this->height();
    QDesktopWidget w;
    int deskWidth = w.availableGeometry().width();
    int deskHeight = w.availableGeometry().height();
    QPoint movePoint(deskWidth / 2 - frmX / 2, deskHeight / 2 - frmY / 2);
    this->move(movePoint);
}

frmMain::~frmMain()
{
    TrayIcon::Instance()->closeAll();
    delete ui;
}

void frmMain::initForm()
{
    setWindowTitle("自定义控件使用示例(qq:517216493)");

    QStringList dialogNames;
    QList<QPushButton *> btns = this->findChildren<QPushButton *>();

    foreach (QPushButton *btn, btns) {
        connect(btn, SIGNAL(pressed()), this, SLOT(btnClick()));
        QString name = btn->objectName();
        dialogNames.append(QString("frm%1").arg(name.mid(3, name.length())));
    }

    //设置遮罩层
    MaskWidget::Instance()->setMainWidget(this);
    MaskWidget::Instance()->setDialogNames(dialogNames);

    //设置托盘
    TrayIcon::Instance()->setIcon(":/main.ico");
    TrayIcon::Instance()->setToolTip(this->windowTitle());
    TrayIcon::Instance()->setMainWidget(this);
}

void frmMain::btnClick()
{
    QPushButton *btn = (QPushButton *)sender();
    QWidget *w = 0;

    if (btn == ui->btnGaugeArc) {
        w = new frmGaugeArc;
    } else if (btn == ui->btnGaugeSpeed) {
        w = new frmGaugeSpeed;
    } else if (btn == ui->btnGaugeCar) {
        w = new frmGaugeCar;
    } else if (btn == ui->btnGaugeClock) {
        w = new frmGaugeClock;
    } else if (btn == ui->btnGaugeCompass) {
        w = new frmGaugeCompass;
    } else if (btn == ui->btnGaugeDial) {
        w = new frmGaugeDial;
    } else if (btn == ui->btnGaugeNet) {
        w = new frmGaugeNet;
    } else if (btn == ui->btnGaugeProgressBar) {
        w = new frmGaugeProgressBar;
    } else if (btn == ui->btnGaugeRange) {
        w = new frmGaugeRange;
    } else if (btn == ui->btnGaugeRound) {
        w = new frmGaugeRound;
    } else if (btn == ui->btnGaugeSimple) {
        w = new frmGaugeSimple;
    } else if (btn == ui->btnGaugeWatch) {
        w = new frmGaugeWatch;
    } else if (btn == ui->btnImageCalendar) {
        w = new frmImageCalendar;
    } else if (btn == ui->btnImageClock) {
        w = new frmImageClock;
    } else if (btn == ui->btnImagePilot) {
        w = new frmImagePilot;
    } else if (btn == ui->btnImagePower) {
        w = new frmImagePower;
    } else if (btn == ui->btnImageView) {
        w = new frmImageView;
    } else if (btn == ui->btnAnimationButton) {
        w = new frmAnimationButton;
    } else if (btn == ui->btnBarRuler) {
        w = new frmBarRuler;
    } else if (btn == ui->btnBarScale) {
        w = new frmBarScale;
    } else if (btn == ui->btnBarTemp) {
        w = new frmBarTemp;
    } else if (btn == ui->btnBarVolumn) {
        w = new frmBarVolume;
    } else if (btn == ui->btnBattery) {
        w = new frmBattery;
    } else if (btn == ui->btnCpuMemoryLabel) {
        w = new frmCpuMemoryLabel;
    } else if (btn == ui->btnCurveChart) {
        w = new frmCurveChart;
    } else if (btn == ui->btnDateTimeLcd) {
        w = new frmDateTimeLcd;
    } else if (btn == ui->btnDeviceSizeTable) {
        w = new frmDeviceSizeTable;
    } else if (btn == ui->btnLcdNumber) {
        w = new frmLcdNumber;
    } else if (btn == ui->btnLedNumber) {
        w = new frmLedNumber;
    } else if (btn == ui->btnLedText) {
        w = new frmLedText;
    } else if (btn == ui->btnLightButton) {
        w = new frmLightButton;
    } else if (btn == ui->btnNavLabel) {
        w = new frmNavLabel;
    } else if (btn == ui->btnNavListView) {
        w = new frmNavListView;
    } else if (btn == ui->btnNavListViewForm) {
        w = new frmNavListViewForm;
    } else if (btn == ui->btnNavProgressBar) {
        w = new frmNavProgressBar;
    } else if (btn == ui->btnBottomWidget) {
        w = new frmBottomWidget;
    } else if (btn == ui->btnProgressBarColor) {
        w = new frmProgressBarColor;
    } else if (btn == ui->btnProgressBarPercent) {
        w = new frmProgressBarPercent;
    } else if (btn == ui->btnProgressBarRound) {
        w = new frmProgressBarRound;
    } else if (btn == ui->btnProgressBarWait) {
        w = new frmProgressBarWait;
    } else if (btn == ui->btnRoundCircle) {
        w = new frmRoundCircle;
    } else if (btn == ui->btnRoundWidget) {
        w = new frmRoundWidget;
    } else if (btn == ui->btnSliderBar) {
        w = new frmSliderBar;
    } else if (btn == ui->btnSliderBarForm) {
        w = new frmSliderBarForm;
    } else if (btn == ui->btnSliderRange) {
        w = new frmSliderRange;
    } else if (btn == ui->btnSliderRuler) {
        w = new frmSliderRuler;
    } else if (btn == ui->btnLineRuler) {
        w = new frmLineRuler;
    } else if (btn == ui->btnTumbler) {
        w = new frmTumbler;
    } else if (btn == ui->btnSwitchButton) {
        w = new frmSwitchButton;
    } else if (btn == ui->btnTextMoveWidget) {
        w = new frmTextMoveWidget;
    } else if (btn == ui->btnVerifiedCode) {
        w = new frmVerifiedCode;
    } else if (btn == ui->btnWaveBar) {
        w = new frmWaveBar;
    } else if (btn == ui->btnWaveDouble) {
        w = new frmWaveDouble;
    } else if (btn == ui->btnWaveLine) {
        w = new frmWaveLine;
    } else if (btn == ui->btnWavePlot) {
        w = new frmWavePlot;
    } else if (btn == ui->btnPanelMoveWidget) {
        w = new frmPanelMoveWidget;
    } else if (btn == ui->btnPanelWidget) {
        w = new frmPanelWidget;
    } else if (btn == ui->btnFlatUI) {
        w = new frmFlatUI;
    } else if (btn == ui->btnAdsWidget) {
        w = new frmAdsWidget;
    } else if (btn == ui->btnIconEditor) {
        w = new frmIconEditor;
    } else if (btn == ui->btnComboBox) {
        w = new frmComboBox;
    }

    if (btn == ui->btnScreenWidget) {
        ScreenWidget::Instance()->showFullScreen();
    } else if (btn == ui->btnColorWidget) {
        ColorWidget::Instance()->show();
    } else if (btn == ui->btnMaskWidget) {
        QDialog d;
        d.setObjectName("frmMaskWidget");
        d.setWindowTitle(btn->text());
        d.resize(300, 200);
        d.exec();
    } else if (btn == ui->btnTrayIcon) {
        if (ui->btnTrayIcon->text() == "显示托盘图标") {
            ui->btnTrayIcon->setText("隐藏托盘图标");
            TrayIcon::Instance()->setVisible(true);
            TrayIcon::Instance()->showMessage(this->windowTitle(), "已经最小化到托盘,双击打开!");
        } else {
            ui->btnTrayIcon->setText("显示托盘图标");
            TrayIcon::Instance()->setVisible(false);
        }
    } else if (btn == ui->btnLunarCalendarInfo) {
        QString strHoliday;
        QString strSolarTerms;
        QString strLunarFestival;
        QString strLunarYear;
        QString strLunarMonth;
        QString strLunarDay;

        LunarCalendarInfo::Instance()->getLunarCalendarInfo(2017, 1, 1,
                                                            strHoliday, strSolarTerms, strLunarFestival,
                                                            strLunarYear, strLunarMonth, strLunarDay);
        qDebug() << "节日:" << strHoliday << "二十四节气:" << strSolarTerms << "农历节气:" << strLunarFestival
                 << "农历年:" << strLunarYear << "农历月:" << strLunarMonth << "农历日:" << strLunarDay;
    }

    if (w == 0) {
        return;
    }

    w->setWindowTitle(btn->text());
    w->setAttribute(Qt::WA_ShowModal, true);
    w->setAttribute(Qt::WA_DeleteOnClose, true);
    w->show();
}
