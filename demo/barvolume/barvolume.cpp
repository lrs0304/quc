#pragma execution_character_set("utf-8")

#include "barvolume.h"
#include "qpainter.h"
#include "qtimer.h"
#include "qdebug.h"

BarVolume::BarVolume(QWidget *parent) : QWidget(parent)
{
    value = 0;
    step = 10;
    space = 5;
    padding = 3;
    radius = 5;

    bgColorStart = QColor(100, 100, 100);
    bgColorEnd = QColor(60, 60, 60);

    barBgColor = QColor(167, 167, 167);
    barColorStart = QColor(85, 255, 0);
    barColorMid = QColor(249, 216, 47);
    barColorEnd = QColor(249, 107, 24);
}

void BarVolume::paintEvent(QPaintEvent *)
{
    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //绘制背景
    drawBg(&painter);
    //绘制进度背景
    drawBarBg(&painter);
    //绘制进度
    drawBar(&painter);
}

void BarVolume::drawBg(QPainter *painter)
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

void BarVolume::drawBarBg(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setOpacity(0.4);
    painter->setBrush(barBgColor);

    //每格的步长等于高度 - 上下两个间隔 - (格数-1)*间隔  最后除以格数
    double increment = (double)(height() - (space * 2) - (step - 1) * padding) / step;
    double initY = space;

    for (int i = 0; i < step; i++) {
        QRectF barBgRect(QPointF(space, initY), QPointF(width() - space, initY + increment));
        painter->drawRoundedRect(barBgRect, radius, radius);
        initY += increment + padding;
    }

    painter->restore();
}

void BarVolume::drawBar(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setOpacity(1.0);

    QLinearGradient barGradient(QPointF(0, height() - space), QPointF(0, space));
    barGradient.setColorAt(0.0, barColorStart);
    barGradient.setColorAt(0.5, barColorMid);
    barGradient.setColorAt(1.0, barColorEnd);
    painter->setBrush(barGradient);

    //每格的步长等于高度 - 上下两个间隔 - (格数-1)*间隔  最后除以格数
    double increment = (double)(height() - (space * 2) - (step - 1) * padding) / step;
    double initY = padding * (step - value) + (step - value) * increment + space ;

    for (int i = 0; i < value; i++) {
        QRectF barRect(QPointF(space, initY), QPointF(width() - space, initY + increment));
        painter->drawRoundedRect(barRect, radius, radius);
        initY += increment + padding;
    }

    painter->restore();
}

int BarVolume::getValue() const
{
    return this->value;
}

int BarVolume::getStep() const
{
    return this->step;
}

int BarVolume::getSpace() const
{
    return this->space;
}

int BarVolume::getPadding() const
{
    return this->padding;
}

int BarVolume::getRadius() const
{
    return this->radius;
}

QColor BarVolume::getBgColorStart() const
{
    return this->bgColorStart;
}

QColor BarVolume::getBgColorEnd() const
{
    return this->bgColorEnd;
}

QColor BarVolume::getBarBgColor() const
{
    return this->barBgColor;
}

QColor BarVolume::getBarColorStart() const
{
    return this->barColorStart;
}

QColor BarVolume::getBarColorMid() const
{
    return this->barColorMid;
}

QColor BarVolume::getBarColorEnd() const
{
    return this->barColorEnd;
}

QSize BarVolume::sizeHint() const
{
    return QSize(100, 300);
}

QSize BarVolume::minimumSizeHint() const
{
    return QSize(10, 30);
}

void BarVolume::setValue(int value)
{
    if (this->value != value && value <= step) {
        this->value = value;
        update();
    }
}

void BarVolume::setStep(int step)
{
    if (this->step != step && value <= step) {
        this->step = step;
        update();
    }
}

void BarVolume::setSpace(int space)
{
    if (this->space != space) {
        this->space = space;
        update();
    }
}

void BarVolume::setPadding(int padding)
{
    if (this->padding != padding) {
        this->padding = padding;
        update();
    }
}

void BarVolume::setRadius(int radius)
{
    if (this->radius != radius) {
        this->radius = radius;
        update();
    }
}

void BarVolume::setBgColorStart(QColor bgColorStart)
{
    if (this->bgColorStart != bgColorStart) {
        this->bgColorStart = bgColorStart;
        update();
    }
}

void BarVolume::setBgColorEnd(QColor bgColorEnd)
{
    if (this->bgColorEnd != bgColorEnd) {
        this->bgColorEnd = bgColorEnd;
        update();
    }
}

void BarVolume::setBarBgColor(QColor barBgColor)
{
    if (this->barBgColor != barBgColor) {
        this->barBgColor = barBgColor;
        update();
    }
}

void BarVolume::setBarColorStart(QColor barColorStart)
{
    if (this->barColorStart != barColorStart) {
        this->barColorStart = barColorStart;
        update();
    }
}

void BarVolume::setBarColorMid(QColor barColorMid)
{
    if (this->barColorMid != barColorMid) {
        this->barColorMid = barColorMid;
        update();
    }
}

void BarVolume::setBarColorEnd(QColor barColorEnd)
{
    if (this->barColorEnd != barColorEnd) {
        this->barColorEnd = barColorEnd;
        update();
    }
}
