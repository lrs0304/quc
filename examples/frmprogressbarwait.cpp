#include "frmprogressbarwait.h"
#include "ui_frmprogressbarwait.h"

frmProgressBarWait::frmProgressBarWait(QWidget *parent) :
	QWidget(parent),
    ui(new Ui::frmProgressBarWait)
{
    ui->setupUi(this);
}

frmProgressBarWait::~frmProgressBarWait()
{
	delete ui;
}
