#pragma execution_character_set("utf-8")

#include "vumeter.h"
#include "qpainter.h"
#include "qmath.h"
#include "qtimer.h"
#include "qdebug.h"

VUMeter::VUMeter(QWidget *parent) : QWidget(parent)
{
    minValue = 0;
    maxValue = 100;
    leftValue = 0;
    rightValue = 0;

    colorBg = QColor(60, 60, 60);
    colorValue = Qt::white;
    colorHigh = Qt::red;
    colorLow = Qt::green;
}

VUMeter::~VUMeter()
{

}

void VUMeter::paintEvent(QPaintEvent *)
{
    //绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.setWindow(0, 0, 100, 540);

    //绘制边框
    drawBorder(&painter);
    //绘制柱状音量
    drawBar(&painter);
    //绘制值
    drawValue(&painter);
}

void VUMeter::drawBorder(QPainter *painter)
{
    painter->save();

    QColor light = Qt::white;
    QColor dark = colorBg.darker(140);

    painter->setPen(QPen(colorBg, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    QLinearGradient linGrad(5, 250, 10, 250);
    linGrad.setColorAt(0, light);
    linGrad.setColorAt(1, colorBg);
    linGrad.setSpread(QGradient::PadSpread);
    painter->setBrush(linGrad);
    QRectF border(5, 5, 90, 530);
    painter->drawRoundRect(border, 30, 5);

    QLinearGradient linGrad1(85, 250, 95, 250);
    linGrad1.setColorAt(0, colorBg);
    linGrad1.setColorAt(1, dark);
    linGrad1.setSpread(QGradient::PadSpread);
    painter->setBrush(linGrad1);
    QRectF border1(20, 5, 75, 530);
    painter->drawRoundRect(border1, 30, 5);

    //绘制左右文字
    painter->setPen(QPen(colorValue, 2));
    QRectF Left(20, 505, 25, 20);
    QRectF Right(55, 505, 25, 20);
    QFont valFont("Arial", 12, QFont::Bold);
    painter->setFont(valFont);
    painter->drawText(Left, Qt::AlignCenter, "左");
    painter->drawText(Right, Qt::AlignCenter, "右");

    painter->restore();
}

void VUMeter::drawBar(QPainter *painter)
{
    painter->save();

    QLinearGradient linGrad(50, 0, 50, 500);
    linGrad.setColorAt(0, colorHigh);
    linGrad.setColorAt(1, colorLow);
    linGrad.setSpread(QGradient::PadSpread);
    painter->setBrush(linGrad);

    //绘制柱状条
    QRectF bar3(20, 50, 25, 450);
    painter->drawRect(bar3);
    QRectF bar4(55, 50, 25, 450);
    painter->drawRect(bar4);

    //绘制柱状背景
    painter->setBrush(QColor(40, 40, 40));

    double length = 450.0;
    double leftBar = abs(length * (minValue - leftValue) / (maxValue - minValue));
    double rightBar = abs(length * (minValue - rightValue) / (maxValue - minValue));
    QRectF bar1(20, 50, 25, 450 - leftBar);
    painter->drawRect(bar1);
    QRectF bar2(55, 50, 25, 450 - rightBar);
    painter->drawRect(bar2);

    painter->setPen(QPen(Qt::black, 2));
    for (int i = 0; i <= 60; i++) {
        painter->drawLine(21, 500 - 450 * i / 60, 44, 500 - 450 * i / 60);
        painter->drawLine(56, 500 - 450 * i / 60, 79, 500 - 450 * i / 60);
    }

    painter->restore();
}

void VUMeter::drawValue(QPainter *painter)
{
    painter->save();

    //绘制左右音量值背景
    painter->setBrush(Qt::black);
    painter->drawRect(20, 15, 25, 25);
    painter->drawRect(55, 15, 25, 25);

    //绘制左右音量值背景右侧突出线条,形成立体感
    painter->setPen(Qt::gray);
    painter->drawLine(20, 40, 45, 40);
    painter->drawLine(45, 15, 45, 40);
    painter->drawLine(55, 40, 80, 40);
    painter->drawLine(80, 15, 80, 40);

    //设置音量值字体
    painter->setPen(QPen(colorValue, 1));
    QFont valFont("Arial", 12, QFont::Bold);
    painter->setFont(valFont);

    //绘制左音量值
    QRectF leftR(20, 15, 25, 25);
    QString lVal = QString("%1").arg(leftValue, 0, 'f', 0);
    painter->drawText(leftR, Qt::AlignCenter, lVal);

    //绘制右音量值
    QRectF rightR(55, 15, 25, 25);
    QString rVal = QString("%1").arg(rightValue, 0, 'f', 0);
    painter->drawText(rightR, Qt::AlignCenter, rVal);

    painter->restore();

    //发送音量值改变信号
    emit valueLChanged(leftValue);
    emit valueRChanged(rightValue);
}

QColor VUMeter::getColorBg() const
{
    return this->colorBg;
}

QColor VUMeter::getColorValue() const
{
    return this->colorValue;
}

QColor VUMeter::getColorLow() const
{
    return this->colorLow;
}

QColor VUMeter::getColorHigh() const
{
    return this->colorHigh;
}

double VUMeter::getMinValue() const
{
    return this->minValue;
}

double VUMeter::getMaxValue() const
{
    return this->maxValue;
}

double VUMeter::getLeftValue() const
{
    return this->leftValue;
}

double VUMeter::getRightValue() const
{
    return this->rightValue;
}

void VUMeter::setMinValue(double minValue)
{
    if (this->minValue > maxValue) {
        this->minValue = maxValue;
        this->maxValue = minValue;
    } else {
        this->minValue = minValue;
    }

    update();
}

void VUMeter::setMaxValue(double maxValue)
{
    if (this->maxValue < minValue) {
        this->maxValue = minValue;
        this->minValue = maxValue;
    } else {
        this->maxValue = maxValue;
    }

    update();
}

void VUMeter::setLeftValue(double leftValue)
{
    if (this->leftValue > maxValue) {
        this->leftValue = maxValue;
    } else if (this->leftValue < minValue) {
        this->leftValue = minValue;
    } else {
        this->leftValue = leftValue;
    }

    update();
}

void VUMeter::setRightValue(double rightValue)
{
    if (this->rightValue > maxValue) {
        this->rightValue = maxValue;
    } else if (this->rightValue < minValue) {
        this->rightValue = minValue;
    } else {
        this->rightValue = rightValue;
    }

    update();
}

void VUMeter::setColorBg(const QColor &colorBg)
{
    if (this->colorBg != colorBg) {
        this->colorBg = colorBg;
        update();
    }
}

void VUMeter::setColorValue(const QColor &colorValue)
{
    if (this->colorValue != colorValue) {
        this->colorValue = colorValue;
        update();
    }
}

void VUMeter::setColorHigh(const QColor &colorHigh)
{
    if (this->colorHigh != colorHigh) {
        this->colorHigh = colorHigh;
        update();
    }
}

void VUMeter::setColorLow(const QColor &colorLow)
{
    if (this->colorLow != colorLow) {
        this->colorLow = colorLow;
        update();
    }
}

QSize VUMeter::sizeHint() const
{
    return QSize(100, 540);
}

QSize VUMeter::minimumSizeHint() const
{
    return QSize(10, 54);
}
