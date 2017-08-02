#pragma execution_character_set("utf-8")

#include "gaugeround.h"
#include "qpainter.h"
#include "qtimer.h"
#include "qdebug.h"

GaugeRound::GaugeRound(QWidget *parent) : QWidget(parent)
{    
    minValue = 0;
    maxValue = 100;
    value = 0;
    precision = 0;

    angle = 40;
    unit = "";

    usedColor = QColor(100, 184, 255);
    freeColor = QColor(70, 70, 70);

    rangeTextColor = QColor(137, 137, 137);
    valueTextColor = QColor(52, 155, 218);

    valueBgColor = QColor(239, 239, 239);
    outBgColor = QColor(233, 233, 233);
    centerBgColorStart = QColor(45, 204, 112);
    centerBgColorEnd = QColor(51, 152, 219);

    currentPercent = 0;
    valuePercent = 0;

    timer = new QTimer(this);
    timer->setInterval(10);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateValue()));

    setFont(QFont("Arial", 7));
}

GaugeRound::~GaugeRound()
{
    if (timer->isActive()) {
        timer->stop();
    }
}

void GaugeRound::paintEvent(QPaintEvent *)
{
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    //绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.translate(width / 2, height / 2);    
    painter.scale(side / 200.0, side / 200.0);

    //绘制已使用百分比及未使用百分比进度
    drawDial(&painter);
    //绘制最外框圆形背景
    drawBgOut(&painter);
    //绘制中间圆环渐变背景
    drawBgRound(&painter);
    //绘制最里框百分比文字圆形背景
    drawBgCenter(&painter);
    //绘制范围值及当前值文字
    drawText(&painter);
}

void GaugeRound::drawDial(QPainter *painter)
{
    int radius = 95;
    double lineWidth = 2.5;
    painter->save();
    painter->rotate(angle);

    //设置画笔
    QPen pen = painter->pen();
    pen.setWidthF(lineWidth);
    pen.setCapStyle(Qt::RoundCap);

    //根据起始旋转的角度计算每次坐标需要旋转的角度,按照100等分计算
    //每次旋转的角度=360-(起始角度*2--分左右)/100
    double rotate = (double)(360 - (angle * 2)) / 100;

    //绘制已使用百分比
    pen.setColor(usedColor);
    painter->setPen(pen);

    for (double i = 0; i < currentPercent; i++) {
        painter->drawLine(0, radius, 0, radius / 1.2);
        painter->rotate(rotate);
    }

    //绘制未使用百分比
    pen.setColor(freeColor);
    painter->setPen(pen);

    for (double i = currentPercent; i < 100; i++) {
        painter->drawLine(0, radius, 0, radius / 1.2);
        painter->rotate(rotate);
    }

    painter->restore();
}

void GaugeRound::drawBgOut(QPainter *painter)
{
    int radius = 70;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(outBgColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void GaugeRound::drawBgRound(QPainter *painter)
{
    int radius = 50;
    painter->save();
    QConicalGradient conicalGradient(radius, radius, 90);
    conicalGradient.setColorAt(0, centerBgColorStart);
    conicalGradient.setColorAt(1.0, centerBgColorEnd);
    painter->setPen(Qt::NoPen);
    painter->setBrush(conicalGradient);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void GaugeRound::drawBgCenter(QPainter *painter)
{
    int radius = 30;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(valueBgColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void GaugeRound::drawText(QPainter *painter)
{
    int radius = 100;
    painter->save();

    //绘制百分比文字及范围值文字
    double currentValue = currentPercent * ((maxValue - minValue) / 100) + minValue;

    //如果当前值超过了目标值则取目标值
    if (currentValue > value) {
        currentValue = value;
    }

    QString strValue = QString("%1%2").arg(QString::number(currentValue, 'f', precision)).arg(unit);
    QString strMinValue = QString("%1%2").arg(minValue).arg(unit);
    QString strMaxValue = QString("%1%2").arg(maxValue).arg(unit);

    painter->setFont(QFont("Arial", 13));
    painter->setPen(QPen(valueTextColor));

    QRectF textRect(-radius, -radius, radius * 2, radius * 2);
    painter->drawText(textRect, Qt::AlignCenter, strValue);

    painter->setFont(QFont("Arial", 8));
    painter->setPen(QPen(rangeTextColor));

    QSizeF size = painter->fontMetrics().size(Qt::TextSingleLine, strMinValue);
    painter->drawText(-radius / 2 - size.width() / 2 + 8, 80, strMinValue);
    size = painter->fontMetrics().size(Qt::TextSingleLine, strMaxValue);
    painter->drawText(radius / 2 - size.width() / 2 - 8, 80, strMaxValue);

    painter->restore();
}

void GaugeRound::updateValue()
{
    if (currentPercent >= valuePercent) {
        timer->stop();
        return;
    }

    currentPercent ++;
    update();
}

double GaugeRound::getMinValue() const
{
    return this->minValue;
}

double GaugeRound::getMaxValue() const
{
    return this->maxValue;
}

double GaugeRound::getValue() const
{
    return this->value;
}

int GaugeRound::getPrecision() const
{
    return this->precision;
}

double GaugeRound::getAngle() const
{
    return this->angle;
}

QString GaugeRound::getUnit() const
{
    return this->unit;
}

QColor GaugeRound::getUsedColor() const
{
    return this->usedColor;
}

QColor GaugeRound::getFreeColor() const
{
    return this->freeColor;
}

QColor GaugeRound::getRangeTextColor() const
{
    return this->rangeTextColor;
}

QColor GaugeRound::getValueTextColor() const
{
    return this->valueTextColor;
}

QColor GaugeRound::getValueBgColor() const
{
    return this->valueBgColor;
}

QColor GaugeRound::getOutBgColor() const
{
    return this->outBgColor;
}

QColor GaugeRound::getCenterBgColorStart() const
{
    return this->centerBgColorStart;
}

QColor GaugeRound::getCenterBgColorEnd() const
{
    return this->centerBgColorEnd;
}

QSize GaugeRound::sizeHint() const
{
    return QSize(200, 200);
}

QSize GaugeRound::minimumSizeHint() const
{
    return QSize(30, 30);
}

void GaugeRound::setRange(double minValue, double maxValue)
{
    //如果最小值大于或者等于最大值则不设置
    if (minValue >= maxValue) {
        return;
    }

    if (timer->isActive()) {
        timer->stop();
    }

    currentPercent = 0;
    valuePercent = 100 * (this->value - this->minValue) / (this->maxValue - this->minValue);
    this->minValue = minValue;
    this->maxValue = maxValue;

    //如果目标值不在范围值内,则重新设置目标值
    if (value < minValue || value > maxValue) {
        setValue(value);
    }
}

void GaugeRound::setRange(int minValue, int maxValue)
{
    setRange((double)minValue, (double)maxValue);
}

void GaugeRound::setMinValue(double minValue)
{
    setRange(minValue, maxValue);
}

void GaugeRound::setMaxValue(double maxValue)
{
    setRange(minValue, maxValue);
}

void GaugeRound::setValue(double value)
{
    if (value < minValue) {
        this->value = minValue;
    } else if (value > maxValue) {
        this->value = maxValue;
    } else {
        this->value = value;
    }

    if (timer->isActive()) {
        timer->stop();
    }

    emit valueChanged(this->value);
    currentPercent = 0;
    valuePercent = 100 * (this->value - this->minValue) / (this->maxValue - this->minValue);
    timer->start();
}

void GaugeRound::setValue(int value)
{
    setValue((double)value);
}

void GaugeRound::setAngle(double angle)
{
    if (this->angle != angle) {
        this->angle = angle;
        update();
    }
}

void GaugeRound::setPrecision(int precision)
{
    //最大精确度为 3
    if (precision <= 3 && this->precision != precision) {
        this->precision = precision;
        update();
    }
}

void GaugeRound::setUnit(const QString &unit)
{
    if (this->unit != unit) {
        this->unit = unit;
        update();
    }
}

void GaugeRound::setUsedColor(const QColor &usedColor)
{
    if (this->usedColor != usedColor) {
        this->usedColor = usedColor;
        update();
    }
}

void GaugeRound::setFreeColor(const QColor &freeColor)
{
    if (this->freeColor != freeColor) {
        this->freeColor = freeColor;
        update();
    }
}

void GaugeRound::setRangeTextColor(const QColor &rangeTextColor)
{
    if (this->rangeTextColor != rangeTextColor) {
        this->rangeTextColor = rangeTextColor;
        update();
    }
}

void GaugeRound::setValueTextColor(const QColor &valueTextColor)
{
    if (this->valueTextColor != valueTextColor) {
        this->valueTextColor = valueTextColor;
        update();
    }
}

void GaugeRound::setValueBgColor(const QColor &valueBgColor)
{
    if (this->valueBgColor != valueBgColor) {
        this->valueBgColor = valueBgColor;
        update();
    }
}

void GaugeRound::setOutBgColor(const QColor &outBgColor)
{
    if (this->outBgColor != outBgColor) {
        this->outBgColor = outBgColor;
        update();
    }
}

void GaugeRound::setCenterBgColorStart(const QColor &centerBgColorStart)
{
    if (this->centerBgColorStart != centerBgColorStart) {
        this->centerBgColorStart = centerBgColorStart;
        update();
    }
}

void GaugeRound::setCenterBgColorEnd(const QColor &centerBgColorEnd)
{
    if (this->centerBgColorEnd != centerBgColorEnd) {
        this->centerBgColorEnd = centerBgColorEnd;
        update();
    }
}
