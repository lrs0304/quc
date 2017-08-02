#include "frmlcdnumber.h"
#include "ui_frmlcdnumber.h"
#include "qdatetime.h"
#include "qtimer.h"

frmLcdNumber::frmLcdNumber(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmLcdNumber)
{
    ui->setupUi(this);
    this->initForm();
}

frmLcdNumber::~frmLcdNumber()
{
    delete ui;
}

void frmLcdNumber::initForm()
{
    //初始化随机数种子
    QTime t = QTime::currentTime();
    qsrand(t.msec() + t.second() * 1000);

    QTimer *timer = new QTimer(this);
    timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateValue()));
    timer->start();
    updateValue();
}

void frmLcdNumber::updateValue()
{
    ui->widget1->setNumber(qrand() % 10);
    ui->widget2->setNumber(qrand() % 10);
}
