#include "frmprogressbarpercent.h"
#include "ui_frmprogressbarpercent.h"
#include "progressbarpercent.h"
#include "flatui.h"
#include "qdebug.h"

frmProgressBarPercent::frmProgressBarPercent(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmProgressBarPercent)
{
    ui->setupUi(this);
    this->initForm();
}

frmProgressBarPercent::~frmProgressBarPercent()
{
    delete ui;
}

void frmProgressBarPercent::initForm()
{
    FlatUI::Instance()->setSliderQss(ui->horizontalSlider, "#505050", "#1ABC9C", "#1ABC9C");
    FlatUI::Instance()->setRadioButtonQss(ui->rbtnClockWise, "#D7DBDE", "#1ABC9C");
    FlatUI::Instance()->setRadioButtonQss(ui->rbtn, "#D7DBDE", "#1ABC9C");
    FlatUI::Instance()->setRadioButtonQss(ui->rbtnArc, "#D7DBDE", "#3498DB");
    FlatUI::Instance()->setRadioButtonQss(ui->rbtnPolo, "#D7DBDE", "#3498DB");
    FlatUI::Instance()->setRadioButtonQss(ui->rbtnArcPolo, "#D7DBDE", "#00FFFF");
    FlatUI::Instance()->setRadioButtonQss(ui->rbtnWave, "#D7DBDE", "#3498DB");

    ui->widget2->setUsedColor(QColor(255, 107, 107));
    ui->widget3->setUsedColor(QColor(24, 189, 155));
    ui->widget5->setUsedColor(QColor(255, 107, 107));
    ui->widget6->setUsedColor(QColor(24, 189, 155));

    //    ui->widget2->setTextColor(QColor(255, 107, 107));
    //    ui->widget3->setTextColor(QColor(0, 255, 255));
    //    ui->widget5->setTextColor(QColor(255, 107, 107));
    //    ui->widget6->setTextColor(QColor(0, 255, 255));

    //    ui->widget4->setNullPosition(180);
    //    ui->widget5->setNullPosition(180);
    //    ui->widget6->setNullPosition(180);

    ui->widget4->setShowPercent(false);
    ui->widget5->setShowPercent(false);
    ui->widget6->setShowPercent(false);

    bars.append(ui->widget1);
    bars.append(ui->widget2);
    bars.append(ui->widget3);
    bars.append(ui->widget4);
    bars.append(ui->widget5);
    bars.append(ui->widget6);

    connect(ui->rbtn, SIGNAL(clicked(bool)), this, SLOT(rbtnClick()));
    connect(ui->rbtnClockWise, SIGNAL(clicked(bool)), this, SLOT(rbtnClick()));
    connect(ui->rbtnArc, SIGNAL(clicked(bool)), this, SLOT(rbtnClick()));
    connect(ui->rbtnPolo, SIGNAL(clicked(bool)), this, SLOT(rbtnClick()));
    connect(ui->rbtnArcPolo, SIGNAL(clicked(bool)), this, SLOT(rbtnClick()));
    connect(ui->rbtnWave, SIGNAL(clicked(bool)), this, SLOT(rbtnClick()));

    ui->comboBox->setCurrentIndex(3);
}

void frmProgressBarPercent::rbtnClick()
{
    QRadioButton *rbtn = (QRadioButton *)sender();
    QString text = rbtn->text();

    if (text == "顺时针") {
        foreach (ProgressBarPercent *bar, bars) {
            bar->setClockWise(true);
        }
    } else if (text == "逆时针") {
        foreach (ProgressBarPercent *bar, bars) {
            bar->setClockWise(false);
        }
    } else if (text == "圆弧") {
        foreach (ProgressBarPercent *bar, bars) {
            bar->setPercentStyle(ProgressBarPercent::PercentStyle_Arc);
        }
    } else if (text == "水池") {
        foreach (ProgressBarPercent *bar, bars) {
            bar->setPercentStyle(ProgressBarPercent::PercentStyle_Polo);
        }
    } else if (text == "圆弧水池") {
        foreach (ProgressBarPercent *bar, bars) {
            bar->setPercentStyle(ProgressBarPercent::PercentStyle_Arc_Polo);
        }
    } else if (text == "水纹") {
        foreach (ProgressBarPercent *bar, bars) {
            bar->setPercentStyle(ProgressBarPercent::PercentStyle_Wave);
        }
    }
}

void frmProgressBarPercent::on_comboBox_currentIndexChanged(const QString &arg1)
{
    foreach (ProgressBarPercent *bar, bars) {
        bar->setNullPosition(arg1.toInt());
    }
}
