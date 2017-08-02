#include "frmgaugerange.h"
#include "ui_frmgaugerange.h"
#include "flatui.h"

frmGaugeRange::frmGaugeRange(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmGaugeRange)
{
    ui->setupUi(this);
    FlatUI::Instance()->setSliderQss(ui->horizontalSlider1, 8, "#505050", "#1ABC9C", "#1ABC9C");
    FlatUI::Instance()->setSliderQss(ui->horizontalSlider2, 8, "#505050", "#E74C3C", "#E74C3C");
}

frmGaugeRange::~frmGaugeRange()
{
    delete ui;
}
