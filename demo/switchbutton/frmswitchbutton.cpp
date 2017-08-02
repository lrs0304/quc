#include "frmswitchbutton.h"
#include "ui_frmswitchbutton.h"
#include "switchbutton.h"

frmSwitchButton::frmSwitchButton(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::frmSwitchButton)
{
	ui->setupUi(this);	
}

frmSwitchButton::~frmSwitchButton()
{
	delete ui;
}
