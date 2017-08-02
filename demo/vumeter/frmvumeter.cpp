#include "frmvumeter.h"
#include "ui_frmvumeter.h"

frmVUMeter::frmVUMeter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmVUMeter)
{
    ui->setupUi(this);
}

frmVUMeter::~frmVUMeter()
{
    delete ui;
}
