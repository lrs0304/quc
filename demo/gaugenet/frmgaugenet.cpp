#include "frmgaugenet.h"
#include "ui_frmgaugenet.h"
#include "flatui.h"

frmGaugeNet::frmGaugeNet(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmGaugeNet)
{
    ui->setupUi(this);
    FlatUI::Instance()->setSliderQss(ui->horizontalSlider, "#505050", "#1ABC9C", "#1ABC9C");
}

frmGaugeNet::~frmGaugeNet()
{
    delete ui;
}
