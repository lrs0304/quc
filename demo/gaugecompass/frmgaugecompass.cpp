#include "frmgaugecompass.h"
#include "ui_frmgaugecompass.h"
#include "flatui.h"

frmGaugeCompass::frmGaugeCompass(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmGaugeCompass)
{
    ui->setupUi(this);
    FlatUI::Instance()->setSliderQss(ui->horizontalSlider, "#505050", "#1ABC9C", "#1ABC9C");
}

frmGaugeCompass::~frmGaugeCompass()
{
    delete ui;
}
