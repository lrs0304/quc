#include "frmledtext.h"
#include "ui_frmledtext.h"

frmLedText::frmLedText(QWidget *parent) :
	QWidget(parent),
    ui(new Ui::frmLedText)
{
	ui->setupUi(this);	
}

frmLedText::~frmLedText()
{
	delete ui;
}
