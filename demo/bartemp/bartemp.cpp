#pragma execution_character_set("utf-8")

#include "bartemp.h"
#include "qpainter.h"
#include "qtimer.h"
#include "qdebug.h"

BarTemp::BarTemp(QWidget *parent) : QWidget(parent)
{    
    minValue = 0;
    maxValue = 100;
    value = 0;
    precision = 0;

    longStep = 10;
    shortStep = 2;
    space = 10;

    animation = false;
    animationStep = 0.5;

    bgColorStart = QColor(100, 100, 100);
    bgColorEnd = QColor(60, 60, 60);
    lineColor = QColor(255, 255, 255);

    barBgColor = QColor(230, 230, 230);
    barColor = QColor(100, 184, 255);

    reverse = false;
    currentValue = 0;
    timer = new QTimer(this);
    timer->setInterval(10);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateValue()));

    setFont(QFont("Arial", 8));
    resizeEvent(NULL);
}

BarTemp::~BarTemp()
{
    if (timer->isActive()) {
        timer->stop();
    }
}

void BarTemp::resizeEvent(QResizeEvent *)
{
    //水银柱底部圆的半径为宽高中最小值的 5分之一
    radius = qMin(width(), height()) / 5;
    //水银柱的宽度为底部圆的直径的 3分之一
    barWidth = (radius * 2) / 3;
    barHeight = height() - radius * 2;

    setValue(value);
}

void BarTemp::paintEvent(QPaintEvent *)
{
    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //绘制背景
    drawBg(&painter);
    //绘制标尺及刻度尺
    drawRuler(&painter);
    //绘制水银柱背景,包含水银柱底部圆
    drawBarBg(&painter);
    //绘制当前水银柱,包含水银柱底部圆
    drawBar(&painter);
}

void BarTemp::drawBg(QPainter *painter)
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

void BarTemp::drawBarBg(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(barBgColor);

    int barX = width() / 2 - barWidth / 2;
    int barY = space;
    QRectF barRect(barX, barY, barWidth, barHeight);

    int circleX = width() / 2 - radius;
    //偏移 2 个像素,使得看起来边缘完整
    int circleY = height() - radius * 2 - 2;
    int circleWidth = radius * 2;
    QRectF circleRect(circleX, circleY, circleWidth, circleWidth);

    QPainterPath path;
    path.addRect(barRect);
    path.addEllipse(circleRect);
    path.setFillRule(Qt::WindingFill);
    painter->drawPath(path);
    painter->restore();
}

void BarTemp::drawRuler(QPainter *painter)
{
    painter->save();
    painter->setPen(lineColor);

    int barPercent = barWidth / 8;

    if (barPercent < 2) {
        barPercent = 2;
    }

    //绘制纵向标尺线 往右偏移 5 像素
    double initX = width() / 2 + barWidth / 2 + 5;
    double initY = space + barPercent;
    QPointF topPot(initX, initY);
    QPointF bottomPot(initX, height() - 2 * radius);
    painter->drawLine(topPot, bottomPot);

    //绘制纵向标尺刻度
    double length = height() - 2 * space - 2 * radius;
    //计算每一格移动多少
    double increment = length / (maxValue - minValue);
    //长线条短线条长度
    int longLineLen = 10;
    int shortLineLen = 7;

    //根据范围值绘制刻度值及刻度值
    for (int i = maxValue; i >= minValue; i = i - shortStep) {
        if (i % longStep == 0) {
            QPointF leftPot(initX + longLineLen, initY);
            QPointF rightPot(initX, initY);
            painter->drawLine(leftPot, rightPot);

            QString strValue = QString("%1").arg((double)i, 0, 'f', precision);
            double fontHeight = painter->fontMetrics().height();
            QPointF textPot(initX + longLineLen + 5, initY + fontHeight / 3);
            painter->drawText(textPot, strValue);
        } else {
            if (i % (longStep / 2) == 0) {
                shortLineLen = 7;
            } else {
                shortLineLen = 4;
            }

            QPointF leftPot(initX + shortLineLen, initY);
            QPointF rightPot(initX, initY);
            painter->drawLine(leftPot, rightPot);
        }

        initY += increment * shortStep;
    }

    painter->restore();
}

void BarTemp::drawBar(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(barColor);

    //计算在背景宽度的基础上缩小的百分比, 至少为 2
    int barPercent = barWidth / 8;
    int circlePercent = radius / 6;

    if (barPercent < 2) {
        barPercent = 2;
    }

    if (circlePercent < 2) {
        circlePercent = 2;
    }

    //标尺刻度高度
    double length = height() - 2 * space - 2 * radius;
    //计算每一格移动多少
    double increment = length / (maxValue - minValue);
    //计算标尺的高度
    int rulerHeight = height() - 1 * space - 2 * radius;

    int barX = width() / 2 - barWidth / 2;
    int barY = rulerHeight - (currentValue - minValue) * increment;
    QRectF barRect(barX + barPercent, barY + barPercent, barWidth - barPercent * 2, barHeight + radius - barY);

    int circleX = width() / 2 - radius;
    //偏移 2 个像素,使得看起来边缘完整
    int circleY = height() - radius * 2 - 2;
    int circleWidth = radius * 2 - circlePercent * 2;
    QRectF circleRect(circleX + circlePercent, circleY + circlePercent, circleWidth, circleWidth);

    QPainterPath path;
    path.addRect(barRect);
    path.addEllipse(circleRect);
    path.setFillRule(Qt::WindingFill);
    painter->drawPath(path);
    painter->restore();
}

double BarTemp::getMinValue() const
{
    return this->minValue;
}

double BarTemp::getMaxValue() const
{
    return this->maxValue;
}

double BarTemp::getValue() const
{
    return this->value;
}

int BarTemp::getPrecision() const
{
    return this->precision;
}

int BarTemp::getLongStep() const
{
    return this->longStep;
}

int BarTemp::getShortStep() const
{
    return this->shortStep;
}

int BarTemp::getSpace() const
{
    return this->space;
}

bool BarTemp::getAnimation() const
{
    return this->animation;
}

double BarTemp::getAnimationStep() const
{
    return this->animationStep;
}

QColor BarTemp::getBgColorStart() const
{
    return this->bgColorStart;
}

QColor BarTemp::getBgColorEnd() const
{
    return this->bgColorEnd;
}

QColor BarTemp::getLineColor() const
{
    return this->lineColor;
}

QColor BarTemp::getBarBgColor() const
{
    return this->barBgColor;
}

QColor BarTemp::getBarColor() const
{
    return this->barColor;
}

QSize BarTemp::sizeHint() const
{
    return QSize(130, 350);
}

QSize BarTemp::minimumSizeHint() const
{
    return QSize(20, 50);
}

void BarTemp::setRange(double minValue, double maxValue)
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

void BarTemp::setRange(int minValue, int maxValue)
{
    setRange((double)minValue, (double)maxValue);
}

void BarTemp::setMinValue(double minValue)
{
    setRange(minValue, maxValue);
}

void BarTemp::setMaxValue(double maxValue)
{
    setRange(minValue, maxValue);
}

void BarTemp::setValue(double value)
{
    //值小于最小值或者值大于最大值则无需处理
    if (value < minValue || value > maxValue) {
        return;
    }

    if (value > this->value) {
        reverse = false;
    } else if (value < this->value) {
        reverse = true;
    }

    this->value = value;
    emit valueChanged(value);

    if (!animation) {
        currentValue = this->value;
        update();
    } else {
        timer->start();
    }
}

void BarTemp::setValue(int value)
{
    setValue((double)value);
}

void BarTemp::setPrecision(int precision)
{
    //最大精确度为 3
    if (precision <= 3 && this->precision != precision) {
        this->precision = precision;
        update();
    }
}

void BarTemp::setLongStep(int longStep)
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

void BarTemp::setShortStep(int shortStep)
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

void BarTemp::setSpace(int space)
{
    if (this->space != space) {
        this->space = space;
        update();
    }
}

void BarTemp::setAnimation(bool animation)
{
    if (this->animation != animation) {
        this->animation = animation;
        update();
    }
}

void BarTemp::setAnimationStep(double animationStep)
{
    if (this->animationStep != animationStep) {
        this->animationStep = animationStep;
        update();
    }
}

void BarTemp::setBgColorStart(const QColor &bgColorStart)
{
    if (this->bgColorStart != bgColorStart) {
        this->bgColorStart = bgColorStart;
        update();
    }
}

void BarTemp::setBgColorEnd(const QColor &bgColorEnd)
{
    if (this->bgColorEnd != bgColorEnd) {
        this->bgColorEnd = bgColorEnd;
        update();
    }
}

void BarTemp::setLineColor(const QColor &lineColor)
{
    if (this->lineColor != lineColor) {
        this->lineColor = lineColor;
        update();
    }
}

void BarTemp::setBarBgColor(const QColor &barBgColor)
{
    if (this->barBgColor != barBgColor) {
        this->barBgColor = barBgColor;
        update();
    }
}

void BarTemp::setBarColor(const QColor &barColor)
{
    if (this->barColor != barColor) {
        this->barColor = barColor;
        update();
    }
}

void BarTemp::updateValue()
{
    if (!reverse) {
        if (currentValue >= value) {
            currentValue = value;
            timer->stop();
        } else {
            currentValue += animationStep;
        }
    } else {
        if (currentValue <= value) {
            currentValue = value;
            timer->stop();
        } else {
            currentValue -= animationStep;
        }
    }

    update();
}
