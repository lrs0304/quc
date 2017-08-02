#pragma execution_character_set("utf-8")

#include "sliderrange.h"
#include "qpainter.h"
#include "qevent.h"
#include "qmath.h"
#include "qdebug.h"

SliderRange::SliderRange(QWidget *parent) : QWidget(parent)
{
    leftValue = 40;
    rightValue = 60;
    minValue = 0;
    maxValue = 100;

    borderWidth = 3;
    horizontal = true;

    usedColor = QColor(24, 189, 155);
    freeColor = QColor(70, 70, 70);
    textColor = QColor(80, 80, 80);
    rangeTextColor = QColor(200, 200, 200);
    sliderColor = QColor(250, 250, 250);
    borderColor = QColor(255, 107, 107);

    sliderStyle = SliderStyle_Line;
    sliderBgPercent = SliderBgPercent_0_2;
    sliderPercent = SliderPercent_0_3;

    leftPressed = false;
    rightPressed = false;

    setFont(QFont("Arial", 7));
}

SliderRange::~SliderRange()
{

}

void SliderRange::mousePressEvent(QMouseEvent *e)
{
    if (e->button() & Qt::LeftButton) {
        if (leftSliderRect.contains(e->pos())) {
            leftPressed = true;
            update();
        } else if (rightSliderRect.contains(e->pos())) {
            rightPressed = true;
            update();
        }
    }
}

void SliderRange::mouseReleaseEvent(QMouseEvent *)
{
    leftPressed = false;
    rightPressed = false;
    update();
}

void SliderRange::mouseMoveEvent(QMouseEvent *e)
{
    //指示器选中,并且坐标在范围值内,且不能超过另外指示器坐标
    if (leftPressed) {
        if (e->pos().x() >= rect().x()) {
            int width = this->width();
            double increment = (double)width / (maxValue - minValue);
            int value = e->pos().x() / increment;

            if (value >= minValue && value <= rightValue) {
                leftValue = value;
                emit valueChanged(leftValue, rightValue);
                update();
            }

        }
    } else if (rightPressed) {
        if (e->pos().x() <= rect().width()) {
            int width = this->width();
            double increment = (double)width / (maxValue - minValue);
            int value = e->pos().x() / increment;

            if (value >= leftValue && value <= maxValue) {
                rightValue = value;
                emit valueChanged(leftValue, rightValue);
                update();
            }
        }
    }
}

void SliderRange::paintEvent(QPaintEvent *)
{
    //绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //绘制滑块背景
    drawSliderBg(&painter);

    //根据样式绘制滑块
    if (sliderStyle == SliderStyle_Line) {
        drawSliderLine(&painter);
    } else if (sliderStyle == SliderStyle_Circle) {
        drawSliderCircle(&painter);
    }
}

void SliderRange::drawSliderBg(QPainter *painter)
{
    painter->save();

    int width = this->width();
    int height = this->height();
    int penWidth = height * ((double)sliderBgPercent / 10);
    int radius = penWidth / 2;

    //增加偏移量,是的边缘更加平滑
    int offset = 1;

    QPen pen = painter->pen();
    pen.setWidth(penWidth);
    pen.setColor(freeColor);
    pen.setCapStyle(Qt::RoundCap);

    painter->setPen(pen);
    painter->drawLine(radius + offset, height / 2, width - radius - offset, height / 2);

    painter->restore();
}

void SliderRange::drawSliderLine(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);

    int width = this->width();
    int height = this->height();
    sliderLen = height * ((double)sliderPercent / 10);

    //计算每一格移动多少,然后计算左边指示器所在位置
    double increment = (double)width / (maxValue - minValue);
    int initY = 0;

    //计算左右滑块区域
    leftSliderRect = QRect(leftValue * increment, initY, sliderLen, height);
    rightSliderRect = QRect(rightValue * increment, initY, sliderLen, height);

    //绘制范围值
    int penWidth = height * ((double)sliderBgPercent / 10);

    painter->setBrush(usedColor);
    painter->drawRect(leftSliderRect.x(), (height - penWidth) / 2, rightSliderRect.x() - leftSliderRect.x(), penWidth);

    QPen pen = QPen();
    pen.setWidth(sliderLen);
    pen.setColor(usedColor);
    pen.setCapStyle(Qt::RoundCap);
    painter->setPen(pen);

    //绘制左边值指示器
    painter->drawLine(leftSliderRect.x(), sliderLen, leftSliderRect.x(), height - sliderLen);

    //绘制右边值指示器
    painter->drawLine(rightSliderRect.x(), sliderLen, rightSliderRect.x(), height - sliderLen);

    painter->restore();
}

void SliderRange::drawSliderCircle(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);

    int width = this->width();
    int height = this->height();
    sliderLen = height * ((double)sliderPercent / 10);

    //如果半径超过高度的一半,则说明超出范围,取高度的一半
    if (sliderLen >= height / 2) {
        sliderLen = height / 2 - 1;
    }

    //计算每一格移动多少,然后计算左边指示器所在位置
    double increment = (double)width / (maxValue - minValue);

    //计算初始坐标及圆半径
    int initY = (height - sliderLen * 2) / 2;
    int side = sliderLen * 2;
    int borderSide = side + borderWidth * 2;

    //计算左右滑块区域
    leftSliderRect = QRect(leftValue * increment - sliderLen, initY, side, side);
    rightSliderRect = QRect(rightValue * increment - sliderLen, initY, side, side);

    //绘制范围值
    int penWidth = height * ((double)sliderBgPercent / 10);
    painter->setBrush(usedColor);
    painter->drawRect(leftSliderRect.x() + sliderLen, (height - penWidth) / 2, rightSliderRect.x() - leftSliderRect.x(), penWidth);

    //绘制左边值指示器
    painter->setBrush(borderColor);
    painter->drawEllipse(leftSliderRect.x() - borderWidth, leftSliderRect.y() - borderWidth, borderSide, borderSide);
    painter->setBrush(sliderColor);
    painter->drawEllipse(leftSliderRect);

    //绘制右边值指示器
    painter->setBrush(borderColor);
    painter->drawEllipse(rightSliderRect.x() - borderWidth, rightSliderRect.y() - borderWidth, borderSide, borderSide);
    painter->setBrush(sliderColor);
    painter->drawEllipse(rightSliderRect);

    painter->restore();
}

int SliderRange::getLeftValue() const
{
    return this->leftValue;
}

int SliderRange::getRightValue() const
{
    return this->rightValue;
}

int SliderRange::getMinValue() const
{
    return this->minValue;
}

int SliderRange::getMaxValue() const
{
    return this->maxValue;
}

int SliderRange::getBorderWidth() const
{
    return this->borderWidth;
}

bool SliderRange::getHorizontal() const
{
    return this->horizontal;
}

QColor SliderRange::getUsedColor() const
{
    return this->usedColor;
}

QColor SliderRange::getFreeColor() const
{
    return this->freeColor;
}

QColor SliderRange::getTextColor() const
{
    return this->textColor;
}

QColor SliderRange::getRangeTextColor() const
{
    return this->rangeTextColor;
}

QColor SliderRange::getSliderColor() const
{
    return this->sliderColor;
}

QColor SliderRange::getBorderColor() const
{
    return this->borderColor;
}

SliderRange::SliderStyle SliderRange::getSliderStyle() const
{
    return this->sliderStyle;
}

SliderRange::SliderBgPercent SliderRange::getSliderBgPercent() const
{
    return this->sliderBgPercent;
}

SliderRange::SliderPercent SliderRange::getSliderPercent() const
{
    return this->sliderPercent;
}

QSize SliderRange::sizeHint() const
{
    return QSize(300, 50);
}

QSize SliderRange::minimumSizeHint() const
{
    return QSize(10, 10);
}

void SliderRange::setCurrentRange(int leftValue, int rightValue)
{
    //左边值不能大于右边值
    if (leftValue > rightValue) {
        return;
    }

    //左边值不能小于最小值,右边值不能大于最大值
    if (leftValue < minValue || rightValue > maxValue) {
        return;
    }

    this->leftValue = leftValue;
    this->rightValue = rightValue;
    emit valueChanged(leftValue, rightValue);

    update();
}

void SliderRange::setLeftValue(int leftValue)
{
    setCurrentRange(leftValue, rightValue);
}

void SliderRange::setRightValue(int rightValue)
{
    setCurrentRange(leftValue, rightValue);
}

void SliderRange::setRange(int minValue, int maxValue)
{
    //如果最小值大于或者等于最大值则不设置
    if (minValue >= maxValue) {
        return;
    }

    this->minValue = minValue;
    this->maxValue = maxValue;

    //如果目标值不在范围值内,则重新设置目标值
    if (leftValue < minValue) {
        leftValue = minValue;
    }

    if (rightValue > maxValue) {
        rightValue = maxValue;
    }

    if (leftValue < minValue || rightValue > maxValue) {
        setCurrentRange(leftValue, rightValue);
    }

    update();
}

void SliderRange::setMinValue(int minValue)
{
    setRange(minValue, maxValue);
}

void SliderRange::setMaxValue(int maxValue)
{
    setRange(minValue, maxValue);
}

void SliderRange::setBorderWidth(int borderWidth)
{
    if (this->borderWidth != borderWidth) {
        this->borderWidth = borderWidth;
        update();
    }
}

void SliderRange::setHorizontal(bool horizontal)
{
    if (this->horizontal != horizontal) {
        this->horizontal = horizontal;
        update();
    }
}

void SliderRange::setUsedColor(const QColor &usedColor)
{
    if (this->usedColor != usedColor) {
        this->usedColor = usedColor;
        update();
    }
}

void SliderRange::setFreeColor(const QColor &freeColor)
{
    if (this->freeColor != freeColor) {
        this->freeColor = freeColor;
        update();
    }
}

void SliderRange::setTextColor(const QColor &textColor)
{
    if (this->textColor != textColor) {
        this->textColor = textColor;
        update();
    }
}

void SliderRange::setRangeTextColor(const QColor &rangeTextColor)
{
    if (this->rangeTextColor != rangeTextColor) {
        this->rangeTextColor = rangeTextColor;
        update();
    }
}

void SliderRange::setSliderColor(const QColor &sliderColor)
{
    if (this->sliderColor != sliderColor) {
        this->sliderColor = sliderColor;
        update();
    }
}

void SliderRange::setBorderColor(const QColor &borderColor)
{
    if (this->borderColor != borderColor) {
        this->borderColor = borderColor;
        update();
    }
}

void SliderRange::setSliderStyle(SliderRange::SliderStyle sliderStyle)
{
    if (this->sliderStyle != sliderStyle) {
        this->sliderStyle = sliderStyle;
        update();
    }
}

void SliderRange::setSliderBgPercent(SliderRange::SliderBgPercent sliderBgPercent)
{
    if (this->sliderBgPercent != sliderBgPercent) {
        this->sliderBgPercent = sliderBgPercent;
        update();
    }
}

void SliderRange::setSliderPercent(SliderRange::SliderPercent sliderPercent)
{
    if (this->sliderPercent != sliderPercent) {
        this->sliderPercent = sliderPercent;
        update();
    }
}
