#include "frmgaugespeed.h"
#include "ui_frmgaugespeed.h"
#include "flatui.h"

frmGaugeSpeed::frmGaugeSpeed(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmGaugeSpeed)
{
    ui->setupUi(this);
    FlatUI::Instance()->setSliderQss(ui->horizontalSlider, 8, "#505050", "#1ABC9C", "#1ABC9C");
}

frmGaugeSpeed::~frmGaugeSpeed()
{
    delete ui;
}
