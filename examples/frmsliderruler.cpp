#include "frmsliderruler.h"
#include "ui_frmsliderruler.h"

frmSliderRuler::frmSliderRuler(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::frmSliderRuler)
{
    ui->setupUi(this);
}

frmSliderRuler::~frmSliderRuler()
{
	delete ui;
}
