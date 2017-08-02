#pragma execution_character_set("utf-8")

#include "barscale.h"
#include "qpainter.h"
#include "qdebug.h"

BarScale::BarScale(QWidget *parent) : QWidget(parent)
{    
    minValue = 0;
    maxValue = 100;
    value = 0;
    alarmValue = 90;

    minValueRight = 0;
    maxValueRight = 100;
    valueRight = 0;
    alarmValueRight = 90;

    longStep = 10;
    shortStep = 2;
    longStepRight = 10;
    shortStepRight = 2;

    bgColor = QColor(2, 16, 34);
    scaleColor = QColor(255, 255, 255);
    textColor = QColor(200, 200, 200);
    alarmScaleColor = QColor(255, 107, 107);

    space = 20;
    scaleStyle = ScaleStyle_Single;

    setFont(QFont("Arial", 9));
}

void BarScale::paintEvent(QPaintEvent *)
{
    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //绘制背景
    drawBg(&painter);

    //绘制左边刻度尺
    drawLeftScale(&painter);
    //绘制右边刻度尺
    drawRightScale(&painter);

    //绘制左边刻度值
    drawLeftText(&painter);
    //绘制左边刻度值
    drawRightText(&painter);

    //绘制左边指示器
    drawLeftPointer(&painter);
    //绘制右边指示器
    drawRightPointer(&painter);
}

void BarScale::drawBg(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(bgColor);
    painter->drawRect(rect());
    painter->restore();
}

void BarScale::drawLeftScale(QPainter *painter)
{
    double minValue = this->minValue;
    double maxValue = this->maxValue;
    int longStep = this->longStep;
    int shortStep = this->shortStep;

    painter->save();
    QPen pen = painter->pen();
    pen.setWidth(2);
    pen.setCapStyle(Qt::RoundCap);
    pen.setColor(scaleColor);
    painter->setPen(pen);

    //绘制纵向标尺线
    double initLeftX = space;
    double initY = space;

    //左侧纵向标尺线
    painter->drawLine(QPointF(initLeftX, initY), QPointF(initLeftX, height() - space));

    //绘制纵向标尺刻度
    double length = height() - 2 * space;
    //计算每一格移动多少
    double increment = length / (maxValue - minValue);
    //长线条短线条长度
    int longLineLen = 10;
    int shortLineLen = 7;

    //根据范围值绘制刻度值及刻度值
    for (int i = maxValue; i >= minValue; i = i - shortStep) {
        if (i % longStep == 0) {
            painter->drawLine(QPointF(initLeftX + longLineLen, initY), QPointF(initLeftX, initY));
        } else {
            if (i % (longStep / 2) == 0) {
                shortLineLen = 7;
            } else {
                shortLineLen = 4;
            }

            painter->drawLine(QPointF(initLeftX + shortLineLen, initY), QPointF(initLeftX, initY));
        }

        initY += increment * shortStep;
    }

    painter->restore();
}

void BarScale::drawRightScale(QPainter *painter)
{
    double minValue = this->minValue;
    double maxValue = this->maxValue;
    int longStep = this->longStep;
    int shortStep = this->shortStep;

    //如果是双精度样式,则范围值及步长取右边的范围值及步长
    if (scaleStyle == ScaleStyle_Double) {
        minValue = this->minValueRight;
        maxValue = this->maxValueRight;
        longStep = this->longStepRight;
        shortStep = this->shortStepRight;
    }

    painter->save();
    QPen pen = painter->pen();
    pen.setWidth(2);
    pen.setCapStyle(Qt::RoundCap);
    pen.setColor(scaleColor);
    painter->setPen(pen);

    //绘制纵向标尺线
    double initRightX = this->width() - space;
    double initY = space;

    //右侧纵向标尺线
    painter->drawLine(QPointF(initRightX, initY), QPointF(initRightX, height() - space));

    //绘制纵向标尺刻度
    double length = height() - 2 * space;
    //计算每一格移动多少
    double increment = length / (maxValue - minValue);
    //长线条短线条长度
    int longLineLen = 10;
    int shortLineLen = 7;

    //根据范围值绘制刻度值及刻度值
    for (int i = maxValue; i >= minValue; i = i - shortStep) {
        if (i % longStep == 0) {
            painter->drawLine(QPointF(initRightX - longLineLen, initY), QPointF(initRightX, initY));
        } else {
            if (i % (longStep / 2) == 0) {
                shortLineLen = 7;
            } else {
                shortLineLen = 4;
            }

            painter->drawLine(QPointF(initRightX - shortLineLen, initY), QPointF(initRightX, initY));
        }

        initY += increment * shortStep;
    }

    painter->restore();
}

void BarScale::drawLeftText(QPainter *painter)
{
    double minValue = this->minValue;
    double maxValue = this->maxValue;
    int longStep = this->longStep;
    int shortStep = this->shortStep;

    painter->save();
    painter->setPen(textColor);

    double initCenterX = space;
    double initCenterY = space / 2;

    double initLeftX = space;
    double initLeftY = space;

    //绘制纵向标尺刻度
    double length = this->height() - 2 * space;
    //计算每一格移动多少
    double increment = length / (maxValue - minValue);
    //长线条短线条长度
    int longLineLen = 10;
    int shortLineLen = 7;

    for (int i = maxValue; i >= minValue; i = i - shortStep) {
        if (i % longStep == 0) {
            QString strValue = QString("%1").arg(i);

            if (scaleStyle == ScaleStyle_Single) {
                //中间刻度值
                QRect textRect(initCenterX, initCenterY, this->width() - space * 2, 20);
                painter->drawText(textRect, Qt::AlignCenter, strValue);
            } else if (scaleStyle == ScaleStyle_Double) {
                //左刻度值
                QPointF textLeftPot(initLeftX + longLineLen + shortLineLen, initLeftY + 4);
                painter->drawText(textLeftPot, strValue);
            }
        }

        initCenterY += increment * shortStep;
        initLeftY += increment * shortStep;
    }

    painter->restore();
}

void BarScale::drawRightText(QPainter *painter)
{
    double minValue = this->minValue;
    double maxValue = this->maxValue;
    int longStep = this->longStep;
    int shortStep = this->shortStep;

    //如果是双精度样式,则范围值及步长取右边的范围值及步长
    if (scaleStyle == ScaleStyle_Double) {
        minValue = this->minValueRight;
        maxValue = this->maxValueRight;
        longStep = this->longStepRight;
        shortStep = this->shortStepRight;
    }

    painter->save();
    painter->setPen(textColor);

    double initCenterX = space;
    double initCenterY = space / 2;

    double initRightX = this->width() - space;
    double initRightY = space;

    //绘制纵向标尺刻度
    double length = this->height() - 2 * space;
    //计算每一格移动多少
    double increment = length / (maxValue - minValue);
    //长线条短线条长度
    int longLineLen = 10;
    int shortLineLen = 7;

    for (int i = maxValue; i >= minValue; i = i - shortStep) {
        if (i % longStep == 0) {
            QString strValue = QString("%1").arg(i);

            if (scaleStyle == ScaleStyle_Single) {
                //中间刻度值
                QRect textRect(initCenterX, initCenterY, this->width() - space * 2, 20);
                painter->drawText(textRect, Qt::AlignCenter, strValue);
            } else if (scaleStyle == ScaleStyle_Double) {
                //右刻度值
                double fontWidth = painter->fontMetrics().width(strValue);
                QPointF textRightPot(initRightX - longLineLen - shortLineLen - fontWidth, initRightY + 4);
                painter->drawText(textRightPot, strValue);
            }
        }

        initCenterY += increment * shortStep;
        initRightY += increment * shortStep;
    }

    painter->restore();
}

void BarScale::drawLeftPointer(QPainter *painter)
{
    double minValue = this->minValue;
    double maxValue = this->maxValue;
    double value = this->value;

    painter->save();
    painter->setPen(alarmScaleColor);
    painter->setBrush(alarmScaleColor);

    //找到当前值所在坐标
    double barHeight = this->height() - space * 2;
    double increment = (double)barHeight / (maxValue - minValue);

    int offset = 10;
    double initLeftX = space + offset;
    double initY = this->height() - space - ((value - minValue) * increment);

    //左侧三角形指示器
    QPolygon leftPts;
    leftPts.append(QPoint(initLeftX, initY));
    leftPts.append(QPoint(initLeftX + offset, initY - offset / 2));
    leftPts.append(QPoint(initLeftX + offset, initY + offset / 2));
    painter->drawPolygon(leftPts);

    painter->restore();
}

void BarScale::drawRightPointer(QPainter *painter)
{
    double minValue = this->minValue;
    double maxValue = this->maxValue;
    double value = this->value;

    //如果是双精度样式,则范围值及步长取右边的范围值及步长
    if (scaleStyle == ScaleStyle_Double) {
        minValue = this->minValueRight;
        maxValue = this->maxValueRight;
        value = this->valueRight;
    }

    painter->save();
    painter->setPen(alarmScaleColor);
    painter->setBrush(alarmScaleColor);

    //找到当前值所在坐标
    double barHeight = this->height() - space * 2;
    double increment = (double)barHeight / (maxValue - minValue);

    int offset = 10;
    double initRightX = this->width() - space - offset;
    double initY = this->height() - space - ((value - minValue) * increment);

    //右侧三角形指示器
    QPolygon rightPts;
    rightPts.append(QPoint(initRightX, initY));
    rightPts.append(QPoint(initRightX - offset, initY - offset / 2));
    rightPts.append(QPoint(initRightX - offset, initY + offset / 2));
    painter->drawPolygon(rightPts);

    painter->restore();
}

double BarScale::getMinValue() const
{
    return this->minValue;
}

double BarScale::getMaxValue() const
{
    return this->maxValue;
}

double BarScale::getValue() const
{
    return this->value;
}

double BarScale::getAlarmValue() const
{
    return this->alarmValue;
}

double BarScale::getMinValueRight() const
{
    return this->minValueRight;
}

double BarScale::getMaxValueRight() const
{
    return this->maxValueRight;
}

double BarScale::getValueRight() const
{
    return this->valueRight;
}

double BarScale::getAlarmValueRight() const
{
    return this->alarmValueRight;
}

int BarScale::getLongStep() const
{
    return this->longStep;
}

int BarScale::getShortStep() const
{
    return this->shortStep;
}

int BarScale::getLongStepRight() const
{
    return this->longStepRight;
}

int BarScale::getShortStepRight() const
{
    return this->shortStepRight;
}

QColor BarScale::getBgColor() const
{
    return this->bgColor;
}

QColor BarScale::getScaleColor() const
{
    return this->scaleColor;
}

QColor BarScale::getTextColor() const
{
    return this->textColor;
}

QColor BarScale::getAlarmScaleColor() const
{
    return this->alarmScaleColor;
}

int BarScale::getSpace() const
{
    return this->space;
}

BarScale::ScaleStyle BarScale::getScaleStyle() const
{
    return this->scaleStyle;
}

QSize BarScale::sizeHint() const
{
    return QSize(120, 300);
}

QSize BarScale::minimumSizeHint() const
{
    return QSize(50, 100);
}

void BarScale::setRange(double minValue, double maxValue)
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

void BarScale::setRange(int minValue, int maxValue)
{
    setRange((double)minValue, (double)maxValue);
}

void BarScale::setRangeRight(double minValueRight, double maxValueRight)
{
    //如果最小值大于或者等于最大值则不设置
    if (minValueRight >= maxValueRight) {
        return;
    }

    this->minValueRight = minValueRight;
    this->maxValueRight = maxValueRight;

    //如果目标值不在范围值内,则重新设置目标值
    if (valueRight < minValueRight || valueRight > maxValueRight) {
        setValueRight(valueRight);
    }

    update();
}

void BarScale::setRangeRight(int minValueRight, int maxValueRight)
{
    setRangeRight((double)minValueRight, (double)maxValueRight);
}

void BarScale::setMinValue(double minValue)
{
    setRange(minValue, maxValue);
}

void BarScale::setMaxValue(double maxValue)
{
    setRange(minValue, maxValue);
}

void BarScale::setMinValueRight(double minValue)
{
    setRangeRight(minValue, maxValue);
}

void BarScale::setMaxValueRight(double maxValue)
{
    setRangeRight(minValue, maxValue);
}

void BarScale::setValue(double value)
{
    //值小于最小值或者值大于最大值则无需处理
    if (value < minValue || value > maxValue) {
        return;
    }

    this->value = value;
    update();
}

void BarScale::setValue(int value)
{
    setValue((double)value);
}

void BarScale::setValueRight(double valueRight)
{
    //值小于最小值或者值大于最大值则无需处理
    if (valueRight < minValueRight || valueRight > maxValueRight) {
        return;
    }

    this->valueRight = valueRight;
    update();
}

void BarScale::setValueRight(int valueRight)
{
    setValueRight((double)valueRight);
}

void BarScale::setAlarmValue(double alarmValue)
{
    if (this->alarmValue != alarmValue) {
        this->alarmValue = alarmValue;
        update();
    }
}

void BarScale::setAlarmValueRight(double alarmValueRight)
{
    if (this->alarmValueRight != alarmValueRight) {
        this->alarmValueRight = alarmValueRight;
        update();
    }
}

void BarScale::setLongStep(int longStep)
{
    //短步长不能超过长步长
    if (longStep < shortStep) {
        return;
    }

    if (this->longStep != longStep) {
        this->longStep = longStep;
        update();
    }
}

void BarScale::setShortStep(int shortStep)
{
    //短步长不能超过长步长
    if (longStep < shortStep) {
        return;
    }

    if (this->shortStep != shortStep) {
        this->shortStep = shortStep;
        update();
    }
}

void BarScale::setLongStepRight(int longStepRight)
{
    //短步长不能超过长步长
    if (longStepRight < shortStepRight) {
        return;
    }

    if (this->longStepRight != longStepRight) {
        this->longStepRight = longStepRight;
        update();
    }
}

void BarScale::setShortStepRight(int shortStepRight)
{
    //短步长不能超过长步长
    if (longStepRight < shortStepRight) {
        return;
    }

    if (this->shortStepRight != shortStepRight) {
        this->shortStepRight = shortStepRight;
        update();
    }
}

void BarScale::setBgColor(QColor bgColor)
{
    if (this->bgColor != bgColor) {
        this->bgColor = bgColor;
        update();
    }
}

void BarScale::setScaleColor(QColor scaleColor)
{
    if (this->scaleColor != scaleColor) {
        this->scaleColor = scaleColor;
        update();
    }
}

void BarScale::setTextColor(QColor textColor)
{
    if (this->textColor != textColor) {
        this->textColor = textColor;
        update();
    }
}

void BarScale::setAlarmScaleColor(QColor alarmScaleColor)
{
    if (this->alarmScaleColor != alarmScaleColor) {
        this->alarmScaleColor = alarmScaleColor;
        update();
    }
}

void BarScale::setSpace(int space)
{
    if (this->space != space) {
        this->space = space;
        update();
    }
}

void BarScale::setScaleStyle(BarScale::ScaleStyle scaleStyle)
{
    if (this->scaleStyle != scaleStyle) {
        this->scaleStyle = scaleStyle;
        update();
    }
}
