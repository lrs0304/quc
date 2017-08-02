#pragma execution_character_set("utf-8")

#include "gaugenet.h"
#include "qpainter.h"
#include "qmath.h"
#include "qtimer.h"
#include "qdebug.h"

GaugeNet::GaugeNet(QWidget *parent) : QWidget(parent)
{    
    minValue = 0;
    maxValue = 20 * 1024;
    value = 0;
    precision = 0;

    scaleMajor = 10;
    scaleMinor = 10;
    startAngle = 45;
    endAngle = 45;

    animation = false;
    animationStep = 1;

    arcColor = QColor(26, 146, 211);
    scaleColor = QColor(26, 146, 211);
    scaleNumColor = QColor(139, 197, 230);
    pointerColor = QColor(255, 107, 107);
    textColor = QColor(70, 244, 66);

    pointerStyle = PointerStyle_IndicatorR;
    scaleStyle = ScaleStyle_Value;

    seconds = 15;
    interval = 100;

    timeValue = 0;
    startTime = QDateTime::currentDateTime();
    timerScale = new QTimer(this);
    timerScale->setInterval(interval);
    connect(timerScale, SIGNAL(timeout()), this, SLOT(updateScale()));

    reverse = false;
    currentValue = 0;
    timer = new QTimer(this);
    timer->setInterval(10);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateValue()));

    setFont(QFont("Arial", 7));
}

GaugeNet::~GaugeNet()
{
    if (timerScale->isActive()) {
        timerScale->stop();
    }

    if (timer->isActive()) {
        timer->stop();
    }
}

void GaugeNet::paintEvent(QPaintEvent *)
{
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    //绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.translate(width / 2, height / 2);    
    painter.scale(side / 200.0, side / 200.0);

    //绘制圆弧
    drawArc(&painter);

    //绘制刻度线
    drawScale(&painter);

    //绘制刻度值
    drawScaleNum(&painter);

    //根据指示器形状绘制指示器
    if (pointerStyle == PointerStyle_Circle) {
        drawPointerCircle(&painter);
    } else if (pointerStyle == PointerStyle_Indicator) {
        drawPointerIndicator(&painter);
    } else if (pointerStyle == PointerStyle_IndicatorR) {
        drawPointerIndicatorR(&painter);
    } else if (pointerStyle == PointerStyle_Triangle) {
        drawPointerTriangle(&painter);
    }

    //绘制指针中心圆外边框
    drawRoundCircle(&painter);
    //绘制指针中心圆
    drawCenterCircle(&painter);
    //绘制当前值
    drawText(&painter);
}

void GaugeNet::drawArc(QPainter *painter)
{
    int radius = 98;
    painter->save();
    painter->setBrush(Qt::NoBrush);
    QPen pen = painter->pen();
    pen.setWidthF(2);

    QColor colorCurrent = arcColor;
    QColor colorOther = textColor;

    //计算总范围角度,当前值范围角度,剩余值范围角度
    double angleAll = 360.0 - startAngle - endAngle;
    double angleCurrent = getRotateByValue(currentValue);

    //如果是按照时间走进度则取当前时间进度
    if (scaleStyle == ScaleStyle_Time) {
        angleCurrent = timeValue;
    }

    double angleOther = angleAll - angleCurrent;

    //绘制外边框圆弧
    QRectF rect = QRectF(-radius, -radius, radius * 2, radius * 2);

    pen.setColor(colorOther);
    painter->setPen(pen);
    painter->drawArc(rect, (270 - startAngle - angleCurrent) * 16, angleCurrent * 16);

    pen.setColor(colorCurrent);
    painter->setPen(pen);
    painter->drawArc(rect, (270 - startAngle - angleCurrent - angleOther) * 16, angleOther * 16);

    //绘制里边框圆弧
    radius = 90;
    rect = QRectF(-radius, -radius, radius * 2, radius * 2);

    pen.setColor(colorOther);
    painter->setPen(pen);
    painter->drawArc(rect, (270 - startAngle - angleCurrent) * 16, angleCurrent * 16);

    pen.setColor(colorCurrent);
    painter->setPen(pen);
    painter->drawArc(rect, (270 - startAngle - angleCurrent - angleOther) * 16, angleOther * 16);

    //增加绘制一条圆弧,加粗,颜色透明度
    radius = 94;
    rect = QRectF(-radius, -radius, radius * 2, radius * 2);

    colorOther.setAlpha(120);
    pen.setColor(colorOther);
    pen.setWidthF(7);
    pen.setCapStyle(Qt::FlatCap);
    painter->setPen(pen);

    painter->drawArc(rect, (270 - startAngle - angleCurrent) * 16, angleCurrent * 16);

    painter->restore();
}

void GaugeNet::drawScale(QPainter *painter)
{
    int radius = 98;
    painter->save();

    scalePen = painter->pen();
    scalePen.setCapStyle(Qt::RoundCap);
    scalePen.setWidthF(1.5);

    painter->rotate(startAngle);
    double angleStep = 7.5;
    int longWidth = 12;
    int shortWidth = 6;

    //绘制0k
    tempValue = 0;
    offset = (double)64 / 6;

    changePen(painter, 0);
    painter->drawLine(0, radius - longWidth, 0, radius);
    painter->rotate(angleStep);

    for (int i = 0; i < 5; i++) {
        changePen(painter, offset);
        tempValue += offset;
        painter->drawLine(0, radius - shortWidth, 0, radius);
        painter->rotate(angleStep);
    }

    //绘制64k
    tempValue = 64;
    offset = (double)64 / 6;

    changePen(painter, 0);
    painter->drawLine(0, radius - longWidth, 0, radius);
    painter->rotate(angleStep);

    for (int i = 0; i < 5; i++) {
        changePen(painter, offset);
        tempValue += offset;
        painter->drawLine(0, radius - shortWidth, 0, radius);
        painter->rotate(angleStep);
    }

    //绘制128k
    tempValue = 128;
    offset = (double)128 / 6;

    changePen(painter, 0);
    painter->drawLine(0, radius - longWidth, 0, radius);
    painter->rotate(angleStep);

    for (int i = 0; i < 5; i++) {
        changePen(painter, offset);
        tempValue += offset;
        painter->drawLine(0, radius - shortWidth, 0, radius);
        painter->rotate(angleStep);
    }

    //绘制256k
    tempValue = 256;
    offset = (double)256 / 6;

    changePen(painter, 0);
    painter->drawLine(0, radius - longWidth, 0, radius);
    painter->rotate(angleStep);

    for (int i = 0; i < 5; i++) {
        changePen(painter, offset);
        tempValue += offset;
        painter->drawLine(0, radius - shortWidth, 0, radius);
        painter->rotate(angleStep);
    }

    //绘制512k
    tempValue = 512;
    offset = (double)512 / 4;

    changePen(painter, 0);
    painter->drawLine(0, radius - longWidth, 0, radius);
    painter->rotate(angleStep);

    for (int i = 0; i < 3; i++) {
        changePen(painter, offset);
        tempValue += offset;
        painter->drawLine(0, radius - shortWidth, 0, radius);
        painter->rotate(angleStep);
    }

    //绘制1M
    tempValue = 1 * 1024;
    offset = (double)(4 * 1024) / 3;

    changePen(painter, 0);
    painter->drawLine(0, radius - longWidth, 0, radius);
    painter->rotate(angleStep);

    for (int i = 0; i < 2; i++) {
        changePen(painter, offset);
        tempValue += offset;
        painter->drawLine(0, radius - shortWidth, 0, radius);
        painter->rotate(angleStep);
    }

    //绘制5M
    tempValue = 5 * 1024;
    offset = (double)(5 * 1024) / 3;

    changePen(painter, 0);
    painter->drawLine(0, radius - longWidth, 0, radius);
    painter->rotate(angleStep);

    for (int i = 0; i < 2; i++) {
        changePen(painter, offset);
        tempValue += offset;
        painter->drawLine(0, radius - shortWidth, 0, radius);
        painter->rotate(angleStep);
    }

    //绘制10M
    tempValue = 10 * 1024;
    offset = (double)(10 * 1024) / 2;

    changePen(painter, 0);
    painter->drawLine(0, radius - longWidth, 0, radius);
    painter->rotate(angleStep);

    for (int i = 0; i < 1; i++) {
        changePen(painter, offset);
        tempValue += offset;
        painter->drawLine(0, radius - shortWidth, 0, radius);
        painter->rotate(angleStep);
    }

    //绘制20M
    tempValue = 20 * 1024;
    offset = (double)(20 * 1024) / 1;

    changePen(painter, 0);
    painter->drawLine(0, radius - longWidth, 0, radius);
    painter->rotate(angleStep);

    painter->restore();
}

void GaugeNet::drawScaleNum(QPainter *painter)
{
    painter->save();
    painter->setPen(scaleNumColor);

    int x = -65;
    int y = 53;
    QString strValue = "0k";
    painter->drawText(x, y, strValue);

    x = -80;
    y = 3;
    strValue = "64k";
    painter->drawText(x, y, strValue);

    x = -65;
    y = -50;
    strValue = "128k";
    painter->drawText(x, y, strValue);

    x = -10;
    y = -75;
    strValue = "256k";
    painter->drawText(x, y, strValue);

    x = 45;
    y = -50;
    strValue = "512k";
    painter->drawText(x, y, strValue);

    x = 65;
    y = -17;
    strValue = "1M";
    painter->drawText(x, y, strValue);

    x = 70;
    y = 15;
    strValue = "5M";
    painter->drawText(x, y, strValue);

    x = 55;
    y = 45;
    strValue = "10M";
    painter->drawText(x, y, strValue);

    painter->restore();
}

void GaugeNet::drawPointerCircle(QPainter *painter)
{
    int radius = 8;
    int offset = 30;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(pointerColor);

    painter->rotate(startAngle);
    painter->rotate(getRotateByValue(currentValue));
    painter->drawEllipse(-radius, radius + offset, radius * 2, radius * 2);

    painter->restore();
}

void GaugeNet::drawPointerIndicator(QPainter *painter)
{
    int radius = 75;
    painter->save();
    painter->setOpacity(0.8);
    painter->setPen(Qt::NoPen);
    painter->setBrush(pointerColor);

    QPolygon pts;
    pts.setPoints(3, -5, 0, 5, 0, 0, radius);

    painter->rotate(startAngle);
    painter->rotate(getRotateByValue(currentValue));
    painter->drawConvexPolygon(pts);

    painter->restore();
}

void GaugeNet::drawPointerIndicatorR(QPainter *painter)
{
    int radius = 65;
    painter->save();
    painter->setPen(pointerColor);
    painter->setBrush(pointerColor);

    QPolygon pts;
    pts.setPoints(3, -5, 0, 5, 0, 0, radius);

    painter->rotate(startAngle);
    painter->rotate(getRotateByValue(currentValue));
    painter->drawConvexPolygon(pts);

    //增加绘制圆角直线,与之前三角形重叠,形成圆角指针
    QPen pen = painter->pen();
    pen.setCapStyle(Qt::RoundCap);
    pen.setWidthF(4);
    painter->setPen(pen);
    painter->drawLine(0, 0, 0, radius);

    painter->restore();
}

void GaugeNet::drawPointerTriangle(QPainter *painter)
{
    int radius = 10;
    int offset = 55;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(pointerColor);

    QPolygon pts;
    pts.setPoints(3, -5, 0 + offset, 5, 0 + offset, 0, radius + offset);

    painter->rotate(startAngle);
    painter->rotate(getRotateByValue(currentValue));
    painter->drawConvexPolygon(pts);

    painter->restore();
}

void GaugeNet::drawRoundCircle(QPainter *painter)
{
    int radius = 12;
    painter->save();
    painter->setOpacity(0.5);
    painter->setPen(Qt::NoPen);
    painter->setBrush(pointerColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void GaugeNet::drawCenterCircle(QPainter *painter)
{
    int radius = 8;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(pointerColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void GaugeNet::drawText(QPainter *painter)
{
    int radius = 100;
    painter->save();
    painter->setPen(textColor);
    painter->setFont(QFont("Arial", 25));

    QRectF textRect(-radius, radius / 2, radius * 2, radius / 3);
    QString strValue = QString("%1").arg((double)currentValue, 0, 'f', precision);

    QRectF unitRect(-radius, radius / 1.3, radius * 2, radius / 4);
    QString strUnit = QString("%1").arg("Kb/s");

    if (value >= 1024) {
        strValue = QString("%1").arg(value / 1024, 0, 'f', 2);
        strUnit = QString("%1").arg("Mb/s");
    }

    painter->drawText(textRect, Qt::AlignCenter, strValue);
    painter->setFont(QFont("Arial", 9));
    painter->drawText(unitRect, Qt::AlignCenter, strUnit);

    painter->restore();
}

void GaugeNet::updateValue()
{
    if (!reverse) {
        if (currentValue >= value) {
            timer->stop();
        } else {
            currentValue += animationStep;
        }
    } else {
        if (currentValue <= value) {
            timer->stop();
        } else {
            currentValue -= animationStep;
        }
    }

    update();
}

void GaugeNet::updateScale()
{
    QDateTime now = QDateTime::currentDateTime();
    if (startTime.secsTo(now) <= (seconds + 1)) {
        //均匀更新刻度尺精度
        double angleAll = 360.0 - startAngle - endAngle;
        double step = (double)angleAll / ((seconds * 1000) / interval);

        if (timeValue <= (angleAll-step)){
            timeValue += step;
        } else {
            timeValue = angleAll;
        }

        scaleValue = getValueByRotate(timeValue);
    } else {
        timerScale->stop();
        update();
    }
}

void GaugeNet::changePen(QPainter *painter, double temp)
{
    double value = currentValue;
    if (scaleStyle == ScaleStyle_Time) {
        value = scaleValue;
    }    

    if ((tempValue + temp) <= value) {
        scalePen.setColor(textColor);
        painter->setPen(scalePen);
    } else {
        scalePen.setColor(scaleColor);
        painter->setPen(scalePen);
    }
}

double GaugeNet::getRotateByValue(double value)
{
    //0 45 90 135 180 210 233 255 270

    double degRotate = 0;
    double offset = 0;
    if (value <= 128) {
        offset = (double)45 / 64;
        degRotate = 0 + (value * offset);
    } else if (value <= 256) {
        offset = (double)45 / 128;
        degRotate = 45 + (value * offset);
    } else if (value <= 512) {
        offset = (double)45 / 256;
        degRotate = 90 + (value * offset);
    } else if (value <= 1024) {
        offset = (double)30 / 512;
        degRotate = 150 + (value * offset);
    } else if (value <= 5 * 1024) {
        offset = (double)30 / (6 * 1024);
        degRotate = 205 + (value * offset);
        if (value == 5 * 1024) {
            degRotate = 233;
        }
    } else if (value <= 10 * 1024) {
        offset = (double)30 / ((double)9 * 1024);
        degRotate = 220 + (value * offset);
        if (value == 10 * 1024) {
            degRotate = 255;
        }
    } else if (value <= 20 * 1024) {
        offset = (double)30 / ((double)20 * 1024);
        degRotate = 240 + (value * offset);
        if (value == 20 * 1024) {
            degRotate = 270;
        }
    }

    //qDebug() << "offset" << offset << "degRotate" << degRotate << "value" << value;
    return degRotate;
}

double GaugeNet::getValueByRotate(double rotate)
{
    //0 45 90 135 180 210 233 255 270

    double value = 0;
    double offset = 0;

    if (rotate <= 90) {
        offset = (double)128 / 90;
        value = 0 + (rotate * offset);
    } else if (rotate <= 135) {
        offset = (double)128 / 45;
        value = 128 + ((rotate - 90) * offset);
    } else if (rotate <= 180) {
        offset = (double)256 / 45;
        value = 256 + ((rotate - 135) * offset);
    } else if (rotate <= 210) {
        offset = (double)512 / 30;
        value = 512 + ((rotate - 180) * offset);
    } else if (rotate <= 233) {
        offset = (double)(4 * 1024) / 23;
        value = (1 * 1024) + ((rotate - 210) * offset);
    } else if (rotate <= 255) {
        offset = (double)(5 * 1024) / 22;
        value = (5 * 1024) + ((rotate - 233) * offset);
    } else if (rotate <= 270) {
        offset = (double)(10 * 1024) / 15;
        value = (10 * 1024) + ((rotate - 255) * offset);
    } else {
        value = 20 * 1024;
    }

    return value;
}

double GaugeNet::getMinValue() const
{
    return this->minValue;
}

double GaugeNet::getMaxValue() const
{
    return this->maxValue;
}

double GaugeNet::getValue() const
{
    return this->value;
}

int GaugeNet::getPrecision() const
{
    return this->precision;
}

int GaugeNet::getScaleMajor() const
{
    return this->scaleMajor;
}

int GaugeNet::getScaleMinor() const
{
    return this->scaleMinor;
}

int GaugeNet::getStartAngle() const
{
    return this->startAngle;
}

int GaugeNet::getEndAngle() const
{
    return this->endAngle;
}

bool GaugeNet::getAnimation() const
{
    return this->animation;
}

double GaugeNet::getAnimationStep() const
{
    return this->animationStep;
}

QColor GaugeNet::getArcColor() const
{
    return this->arcColor;
}

QColor GaugeNet::getScaleColor() const
{
    return this->scaleColor;
}

QColor GaugeNet::getScaleNumColor() const
{
    return this->scaleNumColor;
}

QColor GaugeNet::getPointerColor() const
{
    return this->pointerColor;
}

QColor GaugeNet::getTextColor() const
{
    return this->textColor;
}

GaugeNet::PointerStyle GaugeNet::getPointerStyle() const
{
    return this->pointerStyle;
}

GaugeNet::ScaleStyle GaugeNet::getScaleStyle() const
{
    return this->scaleStyle;
}

int GaugeNet::getSeconds() const
{
    return this->seconds;
}

int GaugeNet::getInterval() const
{
    return this->interval;
}

QSize GaugeNet::sizeHint() const
{
    return QSize(200, 200);
}

QSize GaugeNet::minimumSizeHint() const
{
    return QSize(50, 50);
}

void GaugeNet::setRange(double minValue, double maxValue)
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

void GaugeNet::setRange(int minValue, int maxValue)
{
    setRange((double)minValue, (double)maxValue);
}

void GaugeNet::setMinValue(double minValue)
{
    setRange(minValue, maxValue);
}

void GaugeNet::setMaxValue(double maxValue)
{
    setRange(minValue, maxValue);
}

void GaugeNet::setValue(double value)
{
    //值小于最小值或者值大于最大值或者值和当前值一致则无需处理
    if (value < minValue || value > maxValue || value == this->value) {
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

void GaugeNet::setValue(int value)
{
    setValue((double)value);
}

void GaugeNet::setPrecision(int precision)
{
    //最大精确度为 3
    if (precision <= 3 && this->precision != precision) {
        this->precision = precision;
        update();
    }
}

void GaugeNet::setScaleMajor(int scaleMajor)
{
    if (this->scaleMajor != scaleMajor) {
        this->scaleMajor = scaleMajor;
        update();
    }
}

void GaugeNet::setScaleMinor(int scaleMinor)
{
    if (this->scaleMinor != scaleMinor) {
        this->scaleMinor = scaleMinor;
        update();
    }
}

void GaugeNet::setStartAngle(int startAngle)
{
    if (this->startAngle != startAngle) {
        this->startAngle = startAngle;
        update();
    }
}

void GaugeNet::setEndAngle(int endAngle)
{
    if (this->endAngle != endAngle) {
        this->endAngle = endAngle;
        update();
    }
}

void GaugeNet::setAnimation(bool animation)
{
    if (this->animation != animation) {
        this->animation = animation;
        update();
    }
}

void GaugeNet::setAnimationStep(double animationStep)
{
    if (this->animationStep != animationStep) {
        this->animationStep = animationStep;
        update();
    }
}

void GaugeNet::setArcColor(const QColor &arcColor)
{
    if (this->arcColor != arcColor) {
        this->arcColor = arcColor;
        update();
    }
}

void GaugeNet::setScaleColor(const QColor &scaleColor)
{
    if (this->scaleColor != scaleColor) {
        this->scaleColor = scaleColor;
        update();
    }
}

void GaugeNet::setScaleNumColor(const QColor &scaleNumColor)
{
    if (this->scaleNumColor != scaleNumColor) {
        this->scaleNumColor = scaleNumColor;
        update();
    }
}

void GaugeNet::setPointerColor(const QColor &pointerColor)
{
    if (this->pointerColor != pointerColor) {
        this->pointerColor = pointerColor;
        update();
    }
}

void GaugeNet::setTextColor(const QColor &textColor)
{
    if (this->textColor != textColor) {
        this->textColor = textColor;
        update();
    }
}

void GaugeNet::setPointerStyle(GaugeNet::PointerStyle pointerStyle)
{
    if (this->pointerStyle != pointerStyle) {
        this->pointerStyle = pointerStyle;
        update();
    }
}

void GaugeNet::setScaleStyle(GaugeNet::ScaleStyle scaleStyle)
{
    if (this->scaleStyle != scaleStyle) {
        this->scaleStyle = scaleStyle;
        update();
    }
}

void GaugeNet::setSeconds(int seconds)
{
    if (this->seconds != seconds) {
        this->seconds = seconds;
        update();
    }
}

void GaugeNet::setInterval(int interval)
{
    if (this->interval != interval) {
        this->interval = interval;
        timerScale->setInterval(interval);
        update();
    }
}

void GaugeNet::start()
{
    if (scaleStyle == ScaleStyle_Time) {
        timeValue = 0;
        scaleValue = 0;
        startTime = QDateTime::currentDateTime();
        timerScale->start();
    }
}

void GaugeNet::stop()
{
    if (scaleStyle == ScaleStyle_Time) {
        timeValue = 0;
        scaleValue = 0;
        timerScale->stop();
        update();
    }
}
