#pragma execution_character_set("utf-8")

#include "wavebar.h"
#include "qpainter.h"
#include "qtimer.h"
#include "qdebug.h"

WaveBar::WaveBar(QWidget *parent) :	QWidget(parent)
{    
    minValue = 0;
    maxValue = 100;
    value = 0;

    step = 1.0;
    space = 5;
    headHeight = 3;

    bgColorStart = QColor(100, 100, 100);
    bgColorEnd = QColor(60, 60, 60);
    barColor = QColor(100, 184, 255);

    headY = 0;
    barY = 0;

    barTimer = new QTimer(this);
    barTimer->setInterval(5);
    connect(barTimer, SIGNAL(timeout()), this, SLOT(updateBar()));

    headTimer = new QTimer(this);
    headTimer->setInterval(15);
    connect(headTimer, SIGNAL(timeout()), this, SLOT(updateHead()));
}

WaveBar::~WaveBar()
{
    if (barTimer->isActive()) {
        barTimer->stop();
    }

    if (headTimer->isActive()) {
        headTimer->stop();
    }
}

void WaveBar::resizeEvent(QResizeEvent *)
{
    setValue(value);
}

void WaveBar::paintEvent(QPaintEvent *)
{
    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //绘制渐变背景
    drawBg(&painter);
    //绘制柱状条块
    drawBar(&painter);
    //绘制顶部条块
    drawHead(&painter);
}

void WaveBar::drawBg(QPainter *painter)
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

void WaveBar::drawBar(QPainter *painter)
{
    painter->save();
    QRectF barRect(QPointF(space, barY), QPointF(width() - space, height() - space));
    painter->setPen(Qt::NoPen);
    painter->setBrush(barColor);
    painter->drawRect(barRect);
    painter->restore();
}

void WaveBar::drawHead(QPainter *painter)
{
    painter->save();
    QRectF headRect(QPointF(space, headY), QPointF(width() - space, headY - headHeight));
    painter->setPen(Qt::NoPen);
    painter->setBrush(barColor);
    painter->drawRect(headRect);
    painter->restore();
}

void WaveBar::updateBar()
{
    barY += step;

    //超过底部则停止
    int bottomY = height() - space - headHeight;

    if (barY >= bottomY) {
        if (barTimer->isActive()) {
            barTimer->stop();
        }

        barY = bottomY;
    }

    update();
}

void WaveBar::updateHead()
{
    headY += step;

    //超过底部则停止
    int bottomY = height() - space;

    if (headY >= bottomY) {
        if (headTimer->isActive()) {
            headTimer->stop();
        }

        headY = bottomY;
    }

    update();
}

int WaveBar::getMinValue() const
{
    return this->minValue;
}

int WaveBar::getMaxValue() const
{
    return this->maxValue;
}

int WaveBar::getValue() const
{
    return this->value;
}

double WaveBar::getStep() const
{
    return this->step;
}

int WaveBar::getSpace() const
{
    return this->space;
}

int WaveBar::getHeadHeight() const
{
    return this->headHeight;
}

QColor WaveBar::getBgColorStart() const
{
    return this->bgColorStart;
}

QColor WaveBar::getBgColorEnd() const
{
    return this->bgColorEnd;
}

QColor WaveBar::getBarColor() const
{
    return this->barColor;
}

QSize WaveBar::sizeHint() const
{
    return QSize(50, 200);
}

QSize WaveBar::minimumSizeHint() const
{
    return QSize(10, 20);
}

void WaveBar::setRange(int minValue, int maxValue)
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

void WaveBar::setMinValue(int minValue)
{
    setRange(minValue, maxValue);
}

void WaveBar::setMaxValue(int maxValue)
{
    setRange(minValue, maxValue);
}

void WaveBar::setValue(int value)
{
    //值小于最小值或者值大于最大值则无需处理
    if (value < minValue || value > maxValue) {
        return;
    }

    this->value = value;
    this->currentValue = value;

    //计算差值
    int diff = maxValue - minValue;
    //计算递增量 高度-2*间隔
    double increment = (double)height() / diff;
    headY = height() - (increment * currentValue) + space + headHeight;
    barY = headY;

    //延时启动顶部方块下坠定时器
    barTimer->start();
    QTimer::singleShot(500, headTimer, SLOT(start()));
}

void WaveBar::setStep(double step)
{
    if (this->step != step) {
        this->step = step;
        update();
    }
}

void WaveBar::setSpace(int space)
{
    if (this->space != space) {
        this->space = space;
        update();
    }
}

void WaveBar::setHeadHeight(int headHeight)
{
    if (this->headHeight != headHeight) {
        this->headHeight = headHeight;
        update();
    }
}

void WaveBar::setBgColorStart(const QColor &bgColorStart)
{
    if (this->bgColorStart != bgColorStart) {
        this->bgColorStart = bgColorStart;
        update();
    }
}

void WaveBar::setBgColorEnd(const QColor &bgColorEnd)
{
    if (this->bgColorEnd != bgColorEnd) {
        this->bgColorEnd = bgColorEnd;
        update();
    }
}

void WaveBar::setBarColor(const QColor &barColor)
{
    if (this->barColor != barColor) {
        this->barColor = barColor;
        update();
    }
}
