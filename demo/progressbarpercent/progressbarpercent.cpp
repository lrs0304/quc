#pragma execution_character_set("utf-8")

#include "progressbarpercent.h"
#include "qpainter.h"
#include "qdebug.h"

ProgressBarPercent::ProgressBarPercent(QWidget *parent) : QWidget(parent)
{
    minValue = 0;
    maxValue = 100;
    value = 0;

    nullPosition = 0;
    lineWidth = 10;

    showPercent = true;
    showFree = false;
    showSmallCircle = false;
    clockWise = true;

    usedColor = QColor(100, 184, 255);
    freeColor = QColor(100, 100, 100);
    circleColor = QColor(70, 70, 70);
    textColor = QColor(250, 250, 250);

    percentStyle = PercentStyle_Arc;

    setFont(QFont("Arial", 7));
}

ProgressBarPercent::~ProgressBarPercent()
{
}

void ProgressBarPercent::paintEvent(QPaintEvent *)
{
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    //绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.translate(width / 2, height / 2);
    painter.scale(side / 200.0, side / 200.0);

    //绘制中心圆
    drawCircle(&painter, 99);

    //根据样式绘制进度
    if (percentStyle == PercentStyle_Arc) {
        drawArc(&painter, 99 - lineWidth / 2);
    } else if (percentStyle == PercentStyle_Polo) {
        drawPolo(&painter, 99 - lineWidth);
    } else if (percentStyle == PercentStyle_Arc_Polo) {
        drawArc(&painter, 99 - lineWidth / 2);
        drawPolo(&painter, 99 - lineWidth - lineWidth);
    } else if (percentStyle == PercentStyle_Wave) {
        drawWave(&painter, 100);
    }

    //绘制当前值
    drawText(&painter, 100);
}

void ProgressBarPercent::drawCircle(QPainter *painter, int radius)
{
    if (percentStyle == PercentStyle_Arc) {
        radius = radius - lineWidth;
    } else if (percentStyle == PercentStyle_Arc_Polo) {
        radius = radius - lineWidth * 2;
    }

    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(circleColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void ProgressBarPercent::drawArc(QPainter *painter, int radius)
{
    painter->save();
    painter->setBrush(Qt::NoBrush);

    QPen pen = painter->pen();
    pen.setWidthF(lineWidth);

    //这里可以更改画笔样式更换线条风格
    pen.setCapStyle(Qt::RoundCap);

    double arcLength = 360.0 / (maxValue - minValue) * value;
    QRect rect(-radius, -radius, radius * 2, radius * 2);

    //逆时针为顺时针分负数
    if (!clockWise) {
        arcLength = -arcLength;
    }

    //绘制剩余进度圆弧
    if (showFree) {
        pen.setColor(freeColor);
        painter->setPen(pen);
        painter->drawArc(rect, (nullPosition - arcLength) * 16, -(360 - arcLength) * 16);
    }

    //绘制当前进度圆弧
    pen.setColor(usedColor);
    painter->setPen(pen);
    painter->drawArc(rect, nullPosition * 16, -arcLength * 16);

    //绘制进度圆弧前面的小圆
    if (showSmallCircle) {
        int offset = radius - lineWidth + 1;
        radius = lineWidth / 2 - 1;
        painter->rotate(-nullPosition - 90);

        QRect circleRect(-radius, radius + offset, radius * 2, radius * 2);
        painter->rotate(arcLength);
        painter->drawEllipse(circleRect);
    }

    painter->restore();
}

void ProgressBarPercent::drawPolo(QPainter *painter, int radius)
{
    painter->save();

    //计算当前值所占百分比对应高度
    double poloHeight = (double)radius / (maxValue - minValue) * value;

    //大圆路径
    QPainterPath bigPath;
    bigPath.addEllipse(-radius, -radius, radius * 2, radius * 2);

    //底部水池灌水所占的矩形区域路径
    QPainterPath smallPath;
    smallPath.addRect(-radius, radius - poloHeight * 2, radius * 2, poloHeight * 2);

    //将两个路径重合相交部分提取,就是水池注水所占面积
    QPainterPath path;
    path = bigPath.intersected(smallPath);

    painter->setPen(usedColor);
    painter->setBrush(usedColor);
    painter->drawPath(path);

    painter->restore();
}

void ProgressBarPercent::drawWave(QPainter *painter, int radius)
{

}

void ProgressBarPercent::drawText(QPainter *painter, int radius)
{
    painter->save();
    painter->setPen(textColor);

    int fontSize = 55;
    if (showPercent) {
        fontSize = fontSize - 15;
    }

    painter->setFont(QFont("Arial", fontSize));

    QRectF textRect(-radius, -radius, radius * 2, radius * 2);
    QString strValue = QString("%1").arg(value);

    if (showPercent) {
        strValue = QString("%1%").arg((double)value / (maxValue - minValue) * 100);
    }

    painter->drawText(textRect, Qt::AlignCenter, strValue);

    painter->restore();
}

int ProgressBarPercent::getMinValue() const
{
    return this->minValue;
}

int ProgressBarPercent::getMaxValue() const
{
    return this->maxValue;
}

int ProgressBarPercent::getValue() const
{
    return this->value;
}

int ProgressBarPercent::getNullPosition() const
{
    return this->nullPosition;
}

int ProgressBarPercent::getLineWidth() const
{
    return this->lineWidth;
}

bool ProgressBarPercent::getShowPercent() const
{
    return this->showPercent;
}

bool ProgressBarPercent::getShowFree() const
{
    return this->showFree;
}

bool ProgressBarPercent::getShowSmallCircle() const
{
    return this->showSmallCircle;
}

bool ProgressBarPercent::getClockWise() const
{
    return this->clockWise;
}

QColor ProgressBarPercent::getUsedColor() const
{
    return this->usedColor;
}

QColor ProgressBarPercent::getFreeColor() const
{
    return this->freeColor;
}

QColor ProgressBarPercent::getCircleColor() const
{
    return this->circleColor;
}

QColor ProgressBarPercent::getTextColor() const
{
    return this->textColor;
}

ProgressBarPercent::PercentStyle ProgressBarPercent::getPercentStyle() const
{
    return this->percentStyle;
}

QSize ProgressBarPercent::sizeHint() const
{
    return QSize(200, 200);
}

QSize ProgressBarPercent::minimumSizeHint() const
{
    return QSize(10, 10);
}

void ProgressBarPercent::setRange(int minValue, int maxValue)
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

void ProgressBarPercent::setMinValue(int minValue)
{
    setRange(minValue, maxValue);
}

void ProgressBarPercent::setMaxValue(int maxValue)
{
    setRange(minValue, maxValue);
}

void ProgressBarPercent::setValue(int value)
{
    //值小于最小值或者值大于最大值或者值和当前值一致则无需处理
    if (value < minValue || value > maxValue || value == this->value) {
        return;
    }

    this->value = value;
    update();
    emit valueChanged(value);
}

void ProgressBarPercent::setNullPosition(int nullPosition)
{
    if (this->nullPosition != nullPosition) {
        this->nullPosition = nullPosition;
        update();
    }
}

void ProgressBarPercent::setLineWidth(int lineWidth)
{
    if (this->lineWidth != lineWidth) {
        this->lineWidth = lineWidth;
        update();
    }
}

void ProgressBarPercent::setShowPercent(bool showPercent)
{
    if (this->showPercent != showPercent) {
        this->showPercent = showPercent;
        update();
    }
}

void ProgressBarPercent::setShowFree(bool showFree)
{
    if (this->showFree != showFree) {
        this->showFree = showFree;
        update();
    }
}

void ProgressBarPercent::setShowSmallCircle(bool showSmallCircle)
{
    if (this->showSmallCircle != showSmallCircle) {
        this->showSmallCircle = showSmallCircle;
        update();
    }
}

void ProgressBarPercent::setClockWise(bool clockWise)
{
    if (this->clockWise != clockWise) {
        this->clockWise = clockWise;
        update();
    }
}

void ProgressBarPercent::setUsedColor(const QColor &usedColor)
{
    if (this->usedColor != usedColor) {
        this->usedColor = usedColor;
        update();
    }
}

void ProgressBarPercent::setFreeColor(const QColor &freeColor)
{
    if (this->freeColor != freeColor) {
        this->freeColor = freeColor;
        update();
    }
}

void ProgressBarPercent::setCircleColor(const QColor &circleColor)
{
    if (this->circleColor != circleColor) {
        this->circleColor = circleColor;
        update();
    }
}

void ProgressBarPercent::setTextColor(const QColor &textColor)
{
    if (this->textColor != textColor) {
        this->textColor = textColor;
        update();
    }
}

void ProgressBarPercent::setPercentStyle(ProgressBarPercent::PercentStyle percentStyle)
{
    if (this->percentStyle != percentStyle) {
        this->percentStyle = percentStyle;
        update();
    }
}
