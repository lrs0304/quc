#include "frmgaugedial.h"
#include "ui_frmgaugedial.h"
#include "flatui.h"

frmGaugeDial::frmGaugeDial(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmGaugeDial)
{
    ui->setupUi(this);
    FlatUI::Instance()->setSliderQss(ui->horizontalSlider, 8, "#505050", "#1ABC9C", "#1ABC9C");
}

frmGaugeDial::~frmGaugeDial()
{
    delete ui;
}
