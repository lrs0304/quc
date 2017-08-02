#include "frmbarvolume.h"
#include "ui_frmbarvolume.h"
#include "qdatetime.h"
#include "qtimer.h"

frmBarVolume::frmBarVolume(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::frmBarVolume)
{
	ui->setupUi(this);
	this->initForm();
}

frmBarVolume::~frmBarVolume()
{
	delete ui;
}

void frmBarVolume::initForm()
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

void frmBarVolume::updateValue()
{
    ui->widget1->setValue(qrand() % 10);
    ui->widget2->setValue(qrand() % 10);
    ui->widget3->setValue(qrand() % 10);
    ui->widget4->setValue(qrand() % 10);
    ui->widget5->setValue(qrand() % 10);
}
