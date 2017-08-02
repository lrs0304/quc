#include "frmgaugeprogressbar.h"
#include "ui_frmgaugeprogressbar.h"
#include "flatui.h"

frmGaugeProgressBar::frmGaugeProgressBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmGaugeProgressBar)
{
    ui->setupUi(this);
    FlatUI::Instance()->setSliderQss(ui->horizontalSlider, 8, "#505050", "#1ABC9C", "#1ABC9C");
}

frmGaugeProgressBar::~frmGaugeProgressBar()
{
    delete ui;
}
