#include "frmtumbler.h"
#include "ui_frmtumbler.h"

frmTumbler::frmTumbler(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::frmTumbler)
{
	ui->setupUi(this);
	this->initForm();
}

frmTumbler::~frmTumbler()
{
    delete ui;
}

void frmTumbler::initForm()
{
	ui->widget1->setTextColor(QColor(100, 184, 255));
	ui->widget2->setTextColor(QColor(255, 107, 107));
	ui->widget3->setTextColor(QColor(24, 189, 155));
	ui->widget4->setTextColor(QColor(100, 184, 255));
	ui->widget5->setTextColor(QColor(255, 107, 107));
	ui->widget6->setTextColor(QColor(24, 189, 155));

	QStringList listValue;

	for (int i = 0; i <= 100; i++) {
		listValue.append(QString::number(i));
	}

	ui->widget2->setListValue(listValue);
	ui->widget3->setListValue(listValue);

	ui->widget1->setCurrentIndex(5);
	ui->widget2->setCurrentIndex(30);
	ui->widget3->setCurrentValue("50");

	ui->widget4->setHorizontal(false);
	ui->widget5->setHorizontal(false);
	ui->widget6->setHorizontal(false);

	ui->widget5->setListValue(listValue);
	ui->widget5->setCurrentIndex(10);

	listValue.clear();

	for (int i = 2010; i <= 2030; i++) {
		listValue.append(QString::number(i));
	}

	ui->widget6->setListValue(listValue);
	ui->widget6->setCurrentValue("2016");

	listValue.clear();
	listValue << "Jan" << "Feb" << "Mar" << "Apr" << "May" << "Jun" << "Jul" << "Aug" << "Sep" << "Oct" << "Nov" << "Dec";

	ui->widget4->setListValue(listValue);
	ui->widget4->setCurrentValue("Nov");
}
