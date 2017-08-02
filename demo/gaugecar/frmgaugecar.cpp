#include "frmgaugecar.h"
#include "ui_frmgaugecar.h"
#include "flatui.h"

frmGaugeCar::frmGaugeCar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmGaugeCar)
{
    ui->setupUi(this);
    FlatUI::Instance()->setSliderQss(ui->horizontalSlider, "#505050", "#1ABC9C", "#1ABC9C");
}

frmGaugeCar::~frmGaugeCar()
{
    delete ui;
}
