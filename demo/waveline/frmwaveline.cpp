#include "frmwaveline.h"
#include "ui_frmwaveline.h"
#include "qdatetime.h"
#include "qtimer.h"

frmWaveLine::frmWaveLine(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::frmWaveLine)
{
	ui->setupUi(this);
	this->initForm();
}

frmWaveLine::~frmWaveLine()
{
	delete ui;
}

void frmWaveLine::initForm()
{
	//初始化随机数种子
	QTime t = QTime::currentTime();
	qsrand(t.msec() + t.second() * 1000);

	QTimer *timer = new QTimer(this);
	timer->setInterval(2000);
	connect(timer, SIGNAL(timeout()), this, SLOT(updateValue()));
	timer->start();
	updateValue();
}

void frmWaveLine::updateValue()
{
	QVector<int> data;
	int maxValue = 100;

	for (int i = 0; i < 50; i++) {
		int rand = qrand() % maxValue;
		data.append(rand);
	}

	ui->widget1->setMaxValue(maxValue);
	ui->widget1->setData(data);

	data.clear();
	maxValue = 50;

	for (int i = 0; i < 100; i++) {
		int rand = qrand() % maxValue;
		data.append(rand);
	}

	ui->widget2->setMaxValue(maxValue);
	ui->widget2->setData(data);

	data.clear();
	maxValue = 100;

	for (int i = 0; i < 100; i++) {
		int rand = qrand() % maxValue;
		data.append(rand);
	}

	ui->widget3->setMaxValue(maxValue);
	ui->widget3->setData(data);
}
