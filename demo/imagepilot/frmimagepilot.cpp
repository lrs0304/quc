#include "frmimagepilot.h"
#include "ui_frmimagepilot.h"

frmImagePilot::frmImagePilot(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmImagePilot)
{
    ui->setupUi(this);
}

frmImagePilot::~frmImagePilot()
{
    delete ui;
}
