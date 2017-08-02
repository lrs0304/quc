#include "frmgaugesimple.h"
#include "ui_frmgaugesimple.h"
#include "flatui.h"

frmGaugeSimple::frmGaugeSimple(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmGaugeSimple)
{
    ui->setupUi(this);
    FlatUI::Instance()->setSliderQss(ui->horizontalSlider, "#505050", "#1ABC9C", "#1ABC9C");
}

frmGaugeSimple::~frmGaugeSimple()
{
    delete ui;
}
