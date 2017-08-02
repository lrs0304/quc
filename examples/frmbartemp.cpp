#include "frmbartemp.h"
#include "ui_frmbartemp.h"
#include "qdatetime.h"
#include "qtimer.h"

frmBarTemp::frmBarTemp(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::frmBarTemp)
{
	ui->setupUi(this);
	this->initForm();
}

frmBarTemp::~frmBarTemp()
{
	delete ui;
}

void frmBarTemp::initForm()
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

void frmBarTemp::updateValue()
{
    ui->widget1->setValue(qrand() % 100);
    ui->widget2->setValue(qrand() % 100);
    ui->widget3->setValue(qrand() % 100);
    ui->widget4->setValue(qrand() % 100);
}
