#include "frmwavedouble.h"
#include "ui_frmwavedouble.h"
#include "qdatetime.h"
#include "qtimer.h"

frmWaveDouble::frmWaveDouble(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::frmWaveDouble)
{
	ui->setupUi(this);
	this->initForm();
}

frmWaveDouble::~frmWaveDouble()
{
	delete ui;
}

void frmWaveDouble::initForm()
{
	ui->widget1->setSpace(2);
	ui->widget2->setSpace(2);
	ui->widget3->setSpace(2);
	ui->widget4->setSpace(2);
	ui->widget5->setSpace(2);
	ui->widget6->setSpace(2);
	ui->widget7->setSpace(2);
	ui->widget8->setSpace(2);
	ui->widget9->setSpace(2);
	ui->widget10->setSpace(2);

	ui->widget2->setBarColor(QColor(255, 107, 107));
	ui->widget3->setBarColor(QColor(24, 189, 155));
	ui->widget4->setBarColor(QColor(154, 254, 155));
	ui->widget5->setBarColor(QColor(0, 139, 138));

	ui->widget7->setBarColor(QColor(255, 107, 107));
	ui->widget8->setBarColor(QColor(24, 189, 155));
	ui->widget9->setBarColor(QColor(154, 254, 155));
	ui->widget10->setBarColor(QColor(0, 139, 138));

	//初始化随机数种子
	QTime t = QTime::currentTime();
	qsrand(t.msec() + t.second() * 1000);

	QTimer *timer = new QTimer(this);
	timer->setInterval(2000);
	connect(timer, SIGNAL(timeout()), this, SLOT(updateValue()));
	timer->start();
	updateValue();
}

void frmWaveDouble::updateValue()
{
	ui->widget1->setValue(qrand() % 100);
	ui->widget2->setValue(qrand() % 100);
	ui->widget3->setValue(qrand() % 100);
	ui->widget4->setValue(qrand() % 100);
	ui->widget5->setValue(qrand() % 100);

	ui->widget6->setValue(qrand() % 100);
	ui->widget7->setValue(qrand() % 100);
	ui->widget8->setValue(qrand() % 100);
	ui->widget9->setValue(qrand() % 100);
	ui->widget10->setValue(qrand() % 100);
}
