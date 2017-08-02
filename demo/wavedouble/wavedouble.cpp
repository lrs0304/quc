#pragma execution_character_set("utf-8")

#include "wavedouble.h"
#include "qpainter.h"
#include "qtimer.h"
#include "qdebug.h"

WaveDouble::WaveDouble(QWidget *parent) : QWidget(parent)
{    
    minValue = 0;
    maxValue = 100;
    value = 0;

    step = 1;
    space = 5;

    bgColorStart = QColor(100, 100, 100);
    bgColorEnd = QColor(60, 60, 60);
    barColor = QColor(100, 184, 255);

    currentValue = 0;
    reverse = false;

    timer = new QTimer(this);
    timer->setInterval(10);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateValue()));
}

WaveDouble::~WaveDouble()
{
    stop();
}

void WaveDouble::paintEvent(QPaintEvent *)
{
    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //绘制渐变背景
    drawBg(&painter);
    //绘制柱状条块
    drawBar(&painter);
}

void WaveDouble::drawBg(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient bgGradient(QPointF(0, 0), QPointF(0, height()));
    bgGradient.setColorAt(0.0, bgColorStart);
    bgGradient.setColorAt(1.0, bgColorEnd);
    painter->setBrush(bgGradient);
    painter->drawRect(rect());
    painter->restore();
}

void WaveDouble::drawBar(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(barColor);

    //找到中心点Y轴坐标
    double centerY = (double) height() / 2;
    //每一格递增量
    double increment = (double)(height() - 2 * space) / (maxValue - minValue);
    //找到当前值的起始和结束Y轴坐标 上下两半所以 /2
    double startY = centerY - (currentValue / 2) * increment;
    double endY = centerY + (currentValue / 2) * increment;
    QRectF barRect(QPointF(space, startY), QPointF(width() - space, endY));
    painter->drawRect(barRect);
    painter->restore();
}

int WaveDouble::getMinValue() const
{
    return this->minValue;
}

int WaveDouble::getMaxValue() const
{
    return this->maxValue;
}

int WaveDouble::getValue() const
{
    return this->value;
}

int WaveDouble::getStep() const
{
    return this->step;
}

int WaveDouble::getSpace() const
{
    return this->space;
}

QColor WaveDouble::getBgColorStart() const
{
    return this->bgColorStart;
}

QColor WaveDouble::getBgColorEnd() const
{
    return this->bgColorEnd;
}

QColor WaveDouble::getBarColor() const
{
    return this->barColor;
}

QSize WaveDouble::sizeHint() const
{
    return QSize(50, 200);
}

QSize WaveDouble::minimumSizeHint() const
{
    return QSize(10, 20);
}

void WaveDouble::setRange(int minValue, int maxValue)
{
    //如果最小值大于或者等于最大值则不设置
    if (minValue >= maxValue) {
        return;
    }

    this->minValue = minValue;
    this->maxValue = maxValue;

    //如果目标值不在范围值内,则重新设置目标值
    if (value < minValue || value > maxValue) {
        setValue(value);
    }

    update();
}

void WaveDouble::setMinValue(int minValue)
{
    setRange(minValue, maxValue);
}

void WaveDouble::setMaxValue(int maxValue)
{
    setRange(minValue, maxValue);
}

void WaveDouble::setValue(int value)
{
    if (value > this->value) {
        reverse = false;
    } else if (value < this->value) {
        reverse = true;
    }

    this->value = value;
    emit valueChanged(value);
    timer->start();
}

void WaveDouble::setStep(int step)
{
    if (this->step != step) {
        this->step = step;
        update();
    }
}

void WaveDouble::setSpace(int space)
{
    if (this->space != space) {
        this->space = space;
        update();
    }
}

void WaveDouble::setBgColorStart(const QColor &bgColorStart)
{
    if (this->bgColorStart != bgColorStart) {
        this->bgColorStart = bgColorStart;
        update();
    }
}

void WaveDouble::setBgColorEnd(const QColor &bgColorEnd)
{
    if (this->bgColorEnd != bgColorEnd) {
        this->bgColorEnd = bgColorEnd;
        update();
    }
}

void WaveDouble::setBarColor(const QColor &barColor)
{
    if (this->barColor != barColor) {
        this->barColor = barColor;
        update();
    }
}

void WaveDouble::updateValue()
{
    if (reverse) {
        if (currentValue <= value) {
            currentValue = value;
            stop();
        } else {
            currentValue -= step;
        }
    } else {
        if (currentValue >= value) {
            currentValue = value;
            stop();
        } else {
            currentValue += step;
        }
    }

    update();
}

void WaveDouble::stop()
{
    if (timer->isActive()) {
        timer->stop();
    }
}
