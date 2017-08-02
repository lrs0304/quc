#pragma execution_character_set("utf-8")

#include "roundwidget.h"
#include "qtimer.h"
#include "qmath.h"
#include "qdebug.h"

RoundWidget::RoundWidget(QWidget *parent) : QWidget(parent)
{
    radius = 0;
    circle = 0;
    offset = 0;

    w1 = new QWidget(this);
    w2 = new QWidget(this);
    w3 = new QWidget(this);
    w4 = new QWidget(this);
    w5 = new QWidget(this);
    w6 = new QWidget(this);

    widgets.insert(0, w1);
    widgets.insert(1, w2);
    widgets.insert(2, w3);
    widgets.insert(3, w4);
    widgets.insert(4, w5);
    widgets.insert(5, w6);

    //生成6个widget圆
    initWidget();

    //初始化定时器
    timer = new QTimer(this);
    timer->setInterval(10);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateValue()));
    timer->start();
}

RoundWidget::~RoundWidget()
{
    if (timer->isActive()) {
        timer->stop();
    }
}

void RoundWidget::resizeEvent(QResizeEvent *)
{
    int side = qMin(width(), height());
    radius = (double)side / 6;
    initWidget();
}

void RoundWidget::showEvent(QShowEvent *)
{
    resizeEvent(NULL);
}

void RoundWidget::initWidget()
{
    int width = radius * 2;
    int height = radius * 2;

    QString qss1 = QString("QWidget{background-color:rgba(0,255,255,170);border-radius:%1px}").arg(radius);

    w1->setStyleSheet(qss1);
    w1->setGeometry((170 / 40)*radius, (110 / 40)*radius, width, height);

    QString qss2 = QString("QWidget{background-color:rgba(255,0,255,170);border-radius:%1px}").arg(radius);
    w2->setStyleSheet(qss2);
    w2->setGeometry((150 / 40)*radius, (140 / 40)*radius, width, height);

    QString qss3 = QString("QWidget{background-color:rgba(0,250,0,170);border-radius:%1px}").arg(radius);
    w3->setStyleSheet(qss3);
    w3->setGeometry((100 / 40)*radius, (150 / 40)*radius, width, height);

    QString qss4 = QString("QWidget{background-color:rgba(255,255,0,170);border-radius:%1px}").arg(radius);
    w4->setStyleSheet(qss4);
    w4->setGeometry((70 / 40)*radius, (110 / 40)*radius, width, height);

    QString qss5 = QString("QWidget{background-color:rgba(255,0,0,170);border-radius:%1px}").arg(radius);
    w5->setStyleSheet(qss5);
    w5->setGeometry((90 / 40)*radius, (70 / 40)*radius, width, height);

    QString qss6 = QString("QWidget{background-color:rgba(0,0,255,170);border-radius:%1px}").arg(radius);
    w6->setStyleSheet(qss6);
    w6->setGeometry((150 / 40)*radius, (70 / 40)*radius, width, height);
}

void RoundWidget::updateValue()
{
    circle = circle >= 359 ? 0 : (circle + 3) ;
    offset = offset >= 300 ? -300 : (offset + 6);
    int value = radius + qAbs(offset) / 10;

    for (int i = 0; i < 6; i++) {
        int initX = (110 / 40) * radius + value * sin(circle * (M_PI / 180) + (double)i * (M_PI / 3));
        int initY = (110 / 40) * radius + value * cos(circle * (M_PI / 180) + (double)i * (M_PI / 3));
        widgets.value(i)->move(initX, initY);
    }
}

QSize RoundWidget::sizeHint() const
{
    return QSize(300, 300);
}

QSize RoundWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}
