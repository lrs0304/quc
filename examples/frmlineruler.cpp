#include "frmlineruler.h"
#include "ui_frmlineruler.h"
#include "flatui.h"

frmLineRuler::frmLineRuler(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::frmLineRuler)
{
	ui->setupUi(this);	
    FlatUI::Instance()->setSliderQss(ui->horizontalSlider, 8, "#505050", "#1ABC9C", "#1ABC9C");
}

frmLineRuler::~frmLineRuler()
{
	delete ui;
}
