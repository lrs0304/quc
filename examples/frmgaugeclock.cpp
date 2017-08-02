#include "frmgaugeclock.h"
#include "ui_frmgaugeclock.h"

frmGaugeClock::frmGaugeClock(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmGaugeClock)
{
    ui->setupUi(this);
}

frmGaugeClock::~frmGaugeClock()
{
    delete ui;
}
