#include "frmwavebar.h"
#include "ui_frmwavebar.h"
#include "qdatetime.h"
#include "qtimer.h"

frmWaveBar::frmWaveBar(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::frmWaveBar)
{
	ui->setupUi(this);
    this->initForm();
}

frmWaveBar::~frmWaveBar()
{
	delete ui;
}

void frmWaveBar::resizeEvent(QResizeEvent *)
{
	if (height() <= 300) {
		return;
	}

	double step = height() / 100;
	ui->widget1->setStep(step);
	ui->widget2->setStep(step);
    ui->widget3->setStep(step);
    ui->widget4->setStep(step);
    ui->widget5->setStep(step);
    ui->widget6->setStep(step);
    ui->widget7->setStep(step);
}

void frmWaveBar::initForm()
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

void frmWaveBar::updateValue()
{
    ui->widget1->setValue(qrand() % 100);
    ui->widget2->setValue(qrand() % 100);
    ui->widget3->setValue(qrand() % 100);
    ui->widget4->setValue(qrand() % 100);
    ui->widget5->setValue(qrand() % 100);
    ui->widget6->setValue(qrand() % 100);
    ui->widget7->setValue(qrand() % 100);
}
