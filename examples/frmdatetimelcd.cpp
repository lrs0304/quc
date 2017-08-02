#include "frmdatetimelcd.h"
#include "ui_frmdatetimelcd.h"

frmDateTimeLcd::frmDateTimeLcd(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::frmDateTimeLcd)
{
	ui->setupUi(this);
	this->initForm();
}

frmDateTimeLcd::~frmDateTimeLcd()
{
	delete ui;
}

void frmDateTimeLcd::initForm()
{
	QString qss1 = QString("QLCDNumber{background-color:rgb(0,0,0);color:rgb(%1);}").arg("100,184,255");
	QString qss2 = QString("QLCDNumber{background-color:rgb(0,0,0);color:rgb(%1);}").arg("255,107,107");
	QString qss3 = QString("QLCDNumber{background-color:rgb(0,0,0);color:rgb(%1);}").arg("24,189,155");

	ui->lcdNumber1->setStyleSheet(qss1);
	ui->lcdNumber2->setStyleSheet(qss2);
	ui->lcdNumber3->setStyleSheet(qss3);

	ui->lcdNumber1->start(1000);
	ui->lcdNumber2->start(1000);
	ui->lcdNumber3->start(1000);
}
