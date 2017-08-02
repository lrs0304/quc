#include "frmgaugewatch.h"
#include "ui_frmgaugewatch.h"
#include "flatui.h"

frmGaugeWatch::frmGaugeWatch(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmGaugeWatch)
{
    ui->setupUi(this);
    FlatUI::Instance()->setSliderQss(ui->horizontalSlider, "#505050", "#1ABC9C", "#1ABC9C");
}

frmGaugeWatch::~frmGaugeWatch()
{
    delete ui;
}
