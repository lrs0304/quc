#pragma execution_character_set("utf-8")

#include "gaugerange.h"
#include "qpainter.h"
#include "qmath.h"
#include "qdebug.h"

GaugeRange::GaugeRange(QWidget *parent) : QWidget(parent)
{
    currentValue = 50;
    leftValue = 40;
    rightValue = 60;
    minValue = 0;
    maxValue = 100;

    scaleMajor = 100;
    startAngle = 30;
    endAngle = 30;
    unit = "";

    usedColor = QColor(24, 189, 155);
    freeColor = QColor(70, 70, 70);
    textColor = QColor(80, 80, 80);
    rangeTextColor = QColor(90, 90, 90);

    rangeStyle = RangeStyle_Line;

    setFont(QFont("Arial", 7));
}

GaugeRange::~GaugeRange()
{

}

void GaugeRange::paintEvent(QPaintEvent *)
{
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    //绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.translate(width / 2, height / 2);    
    painter.scale(side / 200.0, side / 200.0);

    //绘制范围刻度线
    if (rangeStyle == RangeStyle_Line) {
        drawRangeLine(&painter);
    } else if (rangeStyle == RangeStyle_Circle) {
        drawRangeCircle(&painter);
    }

    //绘制范围值文字
    drawRangeText(&painter);
    //绘制当前值
    drawText(&painter);
}

void GaugeRange::drawRangeLine(QPainter *painter)
{
    int radius = 99;
    painter->save();

    painter->rotate(startAngle);

    //一个值所经过的步数
    double step = (double)scaleMajor / (maxValue - minValue);

    //范围值左边和右边所在步数临界点
    double leftStep = step * leftValue;
    double rightStep = step * rightValue;

    //每一步旋转经过的角度
    double angleStep = (360.0 - startAngle - endAngle) / scaleMajor;
    QPen pen = painter->pen();
    pen.setCapStyle(Qt::RoundCap);

    for (int i = 0; i <= scaleMajor; i++) {
        //范围值内的颜色突出显示
        if (i >= leftStep && i <= rightStep) {
            pen.setColor(usedColor);
        } else {
            pen.setColor(freeColor);
        }

        pen.setWidthF(1.5);
        painter->setPen(pen);
        painter->drawLine(0, radius - 10, 0, radius);
        painter->rotate(angleStep);
    }

    painter->restore();
}

void GaugeRange::drawRangeCircle(QPainter *painter)
{
    int radius = 95;
    painter->save();
    painter->setBrush(Qt::NoBrush);

    //绘制圆弧方法绘制圆环
    int penWidth = 5;
    QRectF arcRect(-radius + penWidth / 2, -radius + penWidth / 2, radius * 2 - penWidth, radius * 2 - penWidth);
    QPen pen(usedColor, penWidth, Qt::SolidLine, Qt::FlatCap, Qt::MPenJoinStyle);

    //计算总范围角度
    double angleAll = 360.0 - startAngle - endAngle;

    //左边圆右边圆对应旋转角度
    double leftRotate = angleAll / (maxValue - minValue) * (leftValue - minValue);
    double rightRotate = angleAll / (maxValue - minValue) * (rightValue - minValue);

    //绘制圆弧背景
    pen.setColor(freeColor);
    painter->setPen(pen);
    painter->drawArc(arcRect, -(startAngle + endAngle) * 16, angleAll * 16);

    //绘制当前圆弧
    pen.setColor(usedColor);
    painter->setPen(pen);
    painter->drawArc(arcRect, (270 - startAngle - rightRotate) * 16, (rightRotate - leftRotate) * 16);

    painter->restore();

    //绘制范围值两个圆
    radius = 6;
    int offset = 80;

    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(usedColor);
    painter->rotate(startAngle);

    //绘制左边小圆,纠正偏离值
    if (leftValue < (maxValue - minValue) / 2) {
        offset = 81;
    } else {
        offset = 80;
    }

    QRect leftRect(-radius, radius + offset, radius * 2, radius * 2);
    painter->rotate(leftRotate);
    painter->drawEllipse(leftRect);

    //绘制右边小圆,纠正偏离值
    if (rightValue < (maxValue - minValue) / 2) {
        offset = 81;
    } else {
        offset = 80;
    }

    QRect rightRect(-radius, radius + offset, radius * 2, radius * 2);
    painter->rotate(-leftRotate);
    painter->rotate(rightRotate);
    painter->drawEllipse(rightRect);

    painter->restore();
}

void GaugeRange::drawRangeText(QPainter *painter)
{
    int radius = 75;

    painter->save();
    painter->setPen(rangeTextColor);

    QFont font = painter->font();
    font.setPointSize(10);
    painter->setFont(font);

    //一个值所经过的步数
    double step = (double)scaleMajor / (maxValue - minValue);

    //范围值左边和右边所在步数临界点
    double leftStep = step * leftValue;
    double rightStep = step * rightValue;

    double startRad = (360 - startAngle - 90) * (M_PI / 180);
    double deltaRad = (360 - startAngle - endAngle) * (M_PI / 180) / scaleMajor;

    //绘制左边值
    double sina = sin(startRad - leftStep * deltaRad);
    double cosa = cos(startRad - leftStep * deltaRad);
    QString strValue = QString("%1%2").arg(leftValue).arg(unit);
    double textWidth = fontMetrics().width(strValue);
    double textHeight = fontMetrics().height();
    int x = radius * cosa - textWidth / 2;
    int y = -radius * sina + textHeight / 4;
    painter->drawText(x, y, strValue);

    //绘制右边值
    sina = sin(startRad - rightStep * deltaRad);
    cosa = cos(startRad - rightStep * deltaRad);
    strValue = QString("%1%2").arg(rightValue).arg(unit);
    textWidth = fontMetrics().width(strValue);
    textHeight = fontMetrics().height();
    x = radius * cosa - textWidth / 2;
    y = -radius * sina + textHeight / 4;
    painter->drawText(x, y, strValue);

    painter->restore();
}

void GaugeRange::drawText(QPainter *painter)
{
    int radius = 100;
    painter->save();
    painter->setPen(textColor);
    QFont font = painter->font();

    QRectF textRect(-radius, -radius, radius * 2, radius * 2);
    QString strValue = QString("%1%2").arg(currentValue).arg(unit);
    int textWidth = fontMetrics().width(strValue);
    font.setPointSize((radius - textWidth) * 0.6);
    painter->setFont(font);
    painter->drawText(textRect, Qt::AlignCenter, strValue);

    painter->restore();
}

int GaugeRange::getCurrentValue() const
{
    return this->currentValue;
}

int GaugeRange::getLeftValue() const
{
    return this->leftValue;
}

int GaugeRange::getRightValue() const
{
    return this->rightValue;
}

int GaugeRange::getMinValue() const
{
    return this->minValue;
}

int GaugeRange::getMaxValue() const
{
    return this->maxValue;
}

int GaugeRange::getScaleMajor() const
{
    return this->scaleMajor;
}

int GaugeRange::getStartAngle() const
{
    return this->startAngle;
}

int GaugeRange::getEndAngle() const
{
    return this->endAngle;
}

QString GaugeRange::getUnit() const
{
    return this->unit;
}

QColor GaugeRange::getUsedColor() const
{
    return this->usedColor;
}

QColor GaugeRange::getFreeColor() const
{
    return this->freeColor;
}

QColor GaugeRange::getTextColor() const
{
    return this->textColor;
}

QColor GaugeRange::getRangeTextColor() const
{
    return this->rangeTextColor;
}

GaugeRange::RangeStyle GaugeRange::getRangeStyle() const
{
    return this->rangeStyle;
}

QSize GaugeRange::sizeHint() const
{
    return QSize(200, 200);
}

QSize GaugeRange::minimumSizeHint() const
{
    return QSize(50, 50);
}

void GaugeRange::setCurrentValue(int currentValue)
{
    if (currentValue >= leftValue && currentValue <= rightValue) {
        this->currentValue = currentValue;
        update();
    }
}

void GaugeRange::setCurrentRange(int leftValue, int rightValue)
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

void GaugeRange::setLeftValue(int leftValue)
{
    setCurrentRange(leftValue, rightValue);
}

void GaugeRange::setRightValue(int rightValue)
{
    setCurrentRange(leftValue, rightValue);
}

void GaugeRange::setRange(int minValue, int maxValue)
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

void GaugeRange::setMinValue(int minValue)
{
    setRange(minValue, maxValue);
}

void GaugeRange::setMaxValue(int maxValue)
{
    setRange(minValue, maxValue);
}

void GaugeRange::setScaleMajor(int scaleMajor)
{
    if (this->scaleMajor != scaleMajor){
        this->scaleMajor = scaleMajor;
        update();
    }
}

void GaugeRange::setStartAngle(int startAngle)
{
    if (this->startAngle != startAngle){
        this->startAngle = startAngle;
        update();
    }
}

void GaugeRange::setEndAngle(int endAngle)
{
    if (this->endAngle != endAngle){
        this->endAngle = endAngle;
        update();
    }
}

void GaugeRange::setUnit(const QString &unit)
{
    if (this->unit != unit){
        this->unit = unit;
        update();
    }
}

void GaugeRange::setUsedColor(const QColor &usedColor)
{
    if (this->usedColor != usedColor){
        this->usedColor = usedColor;
        update();
    }
}

void GaugeRange::setFreeColor(const QColor &freeColor)
{
    if (this->freeColor != freeColor){
        this->freeColor = freeColor;
        update();
    }
}

void GaugeRange::setTextColor(const QColor &textColor)
{
    if (this->textColor != textColor){
        this->textColor = textColor;
        update();
    }
}

void GaugeRange::setRangeTextColor(const QColor &rangeTextColor)
{
    if (this->rangeTextColor != rangeTextColor){
        this->rangeTextColor = rangeTextColor;
        update();
    }
}

void GaugeRange::setRangeStyle(GaugeRange::RangeStyle rangeStyle)
{
    if (this->rangeStyle != rangeStyle){
        this->rangeStyle = rangeStyle;
        update();
    }
}
