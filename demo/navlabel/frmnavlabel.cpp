#include "frmnavlabel.h"
#include "ui_frmnavlabel.h"
#include "navlabel.h"

frmNavLabel::frmNavLabel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmNavLabel)
{
    ui->setupUi(this);
}

frmNavLabel::~frmNavLabel()
{
    delete ui;
}
