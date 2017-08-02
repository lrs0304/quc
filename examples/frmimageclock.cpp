#include "frmimageclock.h"
#include "ui_frmimageclock.h"

frmImageClock::frmImageClock(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmImageClock)
{
    ui->setupUi(this);
}

frmImageClock::~frmImageClock()
{
    delete ui;
}
