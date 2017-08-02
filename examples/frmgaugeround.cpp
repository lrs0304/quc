#include "frmgaugeround.h"
#include "ui_frmgaugeround.h"
#include "flatui.h"

frmGaugeRound::frmGaugeRound(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmGaugeRound)
{
    ui->setupUi(this);
    FlatUI::Instance()->setSliderQss(ui->horizontalSlider, 8, "#505050", "#1ABC9C", "#1ABC9C");
}

frmGaugeRound::~frmGaugeRound()
{
    delete ui;
}
