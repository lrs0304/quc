#include "frmgaugearc.h"
#include "ui_frmgaugearc.h"
#include "flatui.h"

frmGaugeArc::frmGaugeArc(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmGaugeArc)
{
    ui->setupUi(this);
    FlatUI::Instance()->setSliderQss(ui->horizontalSlider, 8, "#505050", "#1ABC9C", "#1ABC9C");
}

frmGaugeArc::~frmGaugeArc()
{
    delete ui;
}
