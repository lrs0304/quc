#include "frmbattery.h"
#include "ui_frmbattery.h"
#include "flatui.h"

frmBattery::frmBattery(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::frmBattery)
{
    ui->setupUi(this);
    FlatUI::Instance()->setSliderQss(ui->horizontalSlider, 8, "#505050", "#1ABC9C", "#1ABC9C");
    ui->horizontalSlider->setValue(30);
}

frmBattery::~frmBattery()
{
    delete ui;
}
