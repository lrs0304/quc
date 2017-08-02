#include "frmdevicesizetable.h"
#include "ui_frmdevicesizetable.h"

frmDeviceSizeTable::frmDeviceSizeTable(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::frmDeviceSizeTable)
{
	ui->setupUi(this);
}

frmDeviceSizeTable::~frmDeviceSizeTable()
{
	delete ui;
}
