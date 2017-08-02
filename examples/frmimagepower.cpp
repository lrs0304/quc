#include "frmimagepower.h"
#include "ui_frmimagepower.h"

frmImagePower::frmImagePower(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmImagePower)
{
    ui->setupUi(this);
}

frmImagePower::~frmImagePower()
{
    delete ui;
}
