#include "frmsliderrange.h"
#include "ui_frmsliderrange.h"

frmSliderRange::frmSliderRange(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::frmSliderRange)
{
	ui->setupUi(this);
}

frmSliderRange::~frmSliderRange()
{
	delete ui;
}
