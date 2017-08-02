#include "frmroundcircle.h"
#include "ui_frmroundcircle.h"

frmRoundCircle::frmRoundCircle(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::frmRoundCircle)
{
	ui->setupUi(this);
}

frmRoundCircle::~frmRoundCircle()
{
	delete ui;
}
