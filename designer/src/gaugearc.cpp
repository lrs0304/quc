#pragma execution_character_set("utf-8")

#include "gaugearc.h"
#include "qpainter.h"
#include "qmath.h"
#include "qtimer.h"
#include "qdebug.h"

GaugeArc::GaugeArc(QWidget *parent) : QWidget(parent)
{    
    minValue = 0;
    maxValue = 100;
    value = 0;
    precision = 0;

    scaleMajor = 10;
    scaleMinor = 10;
    startAngle = 45;
    endAngle = 45;

    animation = false;
    animationStep = 0.5;

    arcColor = QColor(50, 50, 50);
    scaleColor = QColor(60, 60, 60);
    scaleNumColor = QColor(20, 20, 20);
    pointerColor = QColor(255, 107, 107);
    textColor = QColor(100, 184, 255);

    pointerStyle = PointerStyle_Indicator;

    reverse = false;
    currentValue = 0;
    timer = new QTimer(this);
    timer->setInterval(10);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateValue()));

    setFont(QFont("Arial", 7));
}

GaugeArc::~GaugeArc()
{
    if (timer->isActive()) {
        timer->stop();
    }
}

void GaugeArc::paintEvent(QPaintEvent *)
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

void GaugeArc::drawArc(QPainter *painter)
{
    int radius = 98;
    painter->save();
    QPen pen = painter->pen();
    pen.setColor(arcColor);
    pen.setWidthF(2);

    painter->setPen(pen);
    painter->setBrush(Qt::NoBrush);

    //计算总范围角度,当前值范围角度,剩余值范围角度
    double angleAll = 360.0 - startAngle - endAngle;
    double angleCurrent = angleAll * ((currentValue - minValue) / (maxValue - minValue));
    double angleOther = angleAll - angleCurrent;

    //绘制外边框圆弧
    QRectF rect = QRectF(-radius, -radius, radius * 2, radius * 2);
    painter->drawArc(rect, (270 - startAngle - angleCurrent) * 16, angleCurrent * 16);
    painter->drawArc(rect, (270 - startAngle - angleCurrent - angleOther) * 16, angleOther * 16);

    //绘制里边框圆弧
    radius = 90;
    rect = QRectF(-radius, -radius, radius * 2, radius * 2);
    painter->drawArc(rect, (270 - startAngle - angleCurrent) * 16, angleCurrent * 16);
    painter->drawArc(rect, (270 - startAngle - angleCurrent - angleOther) * 16, angleOther * 16);

    painter->restore();
}

void GaugeArc::drawScale(QPainter *painter)
{
    int radius = 97;
    painter->save();
    painter->setPen(scaleColor);

    painter->rotate(startAngle);
    int steps = (scaleMajor * scaleMinor);
    double angleStep = (360.0 - startAngle - endAngle) / steps;
    QPen pen = painter->pen();
    pen.setCapStyle(Qt::RoundCap);

    for (int i = 0; i <= steps; i++) {
        if (i % scaleMinor == 0) {
            pen.setWidthF(1.5);
            painter->setPen(pen);
            painter->drawLine(0, radius - 12, 0, radius);
        } else {
            pen.setWidthF(1.0);
            painter->setPen(pen);
            painter->drawLine(0, radius - 5, 0, radius);
        }

        painter->rotate(angleStep);
    }

    painter->restore();
}

void GaugeArc::drawScaleNum(QPainter *painter)
{
    int radius = 75;
    painter->save();
    painter->setPen(scaleNumColor);

    double startRad = (360 - startAngle - 90) * (M_PI / 180);
    double deltaRad = (360 - startAngle - endAngle) * (M_PI / 180) / scaleMajor;

    for (int i = 0; i <= scaleMajor; i++) {
        double sina = sin(startRad - i * deltaRad);
        double cosa = cos(startRad - i * deltaRad);
        double value = 1.0 * i * ((maxValue - minValue) / scaleMajor) + minValue;

        QString strValue = QString("%1").arg((double)value, 0, 'f', precision);
        double textWidth = fontMetrics().width(strValue);
        double textHeight = fontMetrics().height();
        int x = radius * cosa - textWidth / 2;
        int y = -radius * sina + textHeight / 4;
        painter->drawText(x, y, strValue);
    }

    painter->restore();
}

void GaugeArc::drawPointerCircle(QPainter *painter)
{
    int radius = 8;
    int offset = 30;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(pointerColor);

    painter->rotate(startAngle);
    double degRotate = (360.0 - startAngle - endAngle) / (maxValue - minValue) * (currentValue - minValue);
    painter->rotate(degRotate);
    painter->drawEllipse(-radius, radius + offset, radius * 2, radius * 2);

    painter->restore();
}

void GaugeArc::drawPointerIndicator(QPainter *painter)
{
    int radius = 75;
    painter->save();
    painter->setOpacity(0.8);
    painter->setPen(Qt::NoPen);
    painter->setBrush(pointerColor);

    QPolygon pts;
    pts.setPoints(3, -5, 0, 5, 0, 0, radius);

    painter->rotate(startAngle);
    double degRotate = (360.0 - startAngle - endAngle) / (maxValue - minValue) * (currentValue - minValue);
    painter->rotate(degRotate);
    painter->drawConvexPolygon(pts);

    painter->restore();
}

void GaugeArc::drawPointerIndicatorR(QPainter *painter)
{
    int radius = 75;
    painter->save();
    painter->setPen(pointerColor);
    painter->setBrush(pointerColor);

    QPolygon pts;
    pts.setPoints(3, -5, 0, 5, 0, 0, radius);

    painter->rotate(startAngle);
    double degRotate = (360.0 - startAngle - endAngle) / (maxValue - minValue) * (currentValue - minValue);
    painter->rotate(degRotate);
    painter->drawConvexPolygon(pts);

    //增加绘制圆角直线,与之前三角形重叠,形成圆角指针
    QPen pen = painter->pen();
    pen.setCapStyle(Qt::RoundCap);
    pen.setWidthF(4);
    painter->setPen(pen);
    painter->drawLine(0, 0, 0, radius);

    painter->restore();
}

void GaugeArc::drawPointerTriangle(QPainter *painter)
{
    int radius = 10;
    int offset = 55;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(pointerColor);

    QPolygon pts;
    pts.setPoints(3, -5, 0 + offset, 5, 0 + offset, 0, radius + offset);

    painter->rotate(startAngle);
    double degRotate = (360.0 - startAngle - endAngle) / (maxValue - minValue) * (currentValue - minValue);
    painter->rotate(degRotate);
    painter->drawConvexPolygon(pts);

    painter->restore();
}

void GaugeArc::drawRoundCircle(QPainter *painter)
{
    int radius = 12;
    painter->save();
    painter->setOpacity(0.5);
    painter->setPen(Qt::NoPen);
    painter->setBrush(pointerColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void GaugeArc::drawCenterCircle(QPainter *painter)
{
    int radius = 8;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(pointerColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void GaugeArc::drawText(QPainter *painter)
{
    int radius = 100;
    painter->save();
    painter->setPen(textColor);
    painter->setFont(QFont("Arial", 25));

    QRectF textRect(-radius, radius / 2, radius * 2, radius / 3);
    QString strValue = QString("%1").arg((double)currentValue, 0, 'f', precision);
    painter->drawText(textRect, Qt::AlignCenter, strValue);

    painter->restore();
}

void GaugeArc::updateValue()
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

double GaugeArc::getMinValue() const
{
    return this->minValue;
}

double GaugeArc::getMaxValue() const
{
    return this->maxValue;
}

double GaugeArc::getValue() const
{
    return this->value;
}

int GaugeArc::getPrecision() const
{
    return this->precision;
}

int GaugeArc::getScaleMajor() const
{
    return this->scaleMajor;
}

int GaugeArc::getScaleMinor() const
{
    return this->scaleMinor;
}

int GaugeArc::getStartAngle() const
{
    return this->startAngle;
}

int GaugeArc::getEndAngle() const
{
    return this->endAngle;
}

bool GaugeArc::getAnimation() const
{
    return this->animation;
}

double GaugeArc::getAnimationStep() const
{
    return this->animationStep;
}

QColor GaugeArc::getArcColor() const
{
    return this->arcColor;
}

QColor GaugeArc::getScaleColor() const
{
    return this->scaleColor;
}

QColor GaugeArc::getScaleNumColor() const
{
    return this->scaleNumColor;
}

QColor GaugeArc::getPointerColor() const
{
    return this->pointerColor;
}

QColor GaugeArc::getTextColor() const
{
    return this->textColor;
}

GaugeArc::PointerStyle GaugeArc::getPointerStyle() const
{
    return this->pointerStyle;
}

QSize GaugeArc::sizeHint() const
{
    return QSize(200, 200);
}

QSize GaugeArc::minimumSizeHint() const
{
    return QSize(50, 50);
}

void GaugeArc::setRange(double minValue, double maxValue)
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

void GaugeArc::setRange(int minValue, int maxValue)
{
    setRange((double)minValue, (double)maxValue);
}

void GaugeArc::setMinValue(double minValue)
{
    setRange(minValue, maxValue);
}

void GaugeArc::setMaxValue(double maxValue)
{
    setRange(minValue, maxValue);
}

void GaugeArc::setValue(double value)
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

void GaugeArc::setValue(int value)
{
    setValue((double)value);
}

void GaugeArc::setPrecision(int precision)
{
    //最大精确度为 3
    if (precision <= 3 && this->precision != precision) {
        this->precision = precision;
        update();
    }
}

void GaugeArc::setScaleMajor(int scaleMajor)
{
    if (this->scaleMajor != scaleMajor) {
        this->scaleMajor = scaleMajor;
        update();
    }
}

void GaugeArc::setScaleMinor(int scaleMinor)
{
    if (this->scaleMinor != scaleMinor) {
        this->scaleMinor = scaleMinor;
        update();
    }
}

void GaugeArc::setStartAngle(int startAngle)
{
    if (this->startAngle != startAngle) {
        this->startAngle = startAngle;
        update();
    }
}

void GaugeArc::setEndAngle(int endAngle)
{
    if (this->endAngle != endAngle) {
        this->endAngle = endAngle;
        update();
    }
}

void GaugeArc::setAnimation(bool animation)
{
    if (this->animation != animation) {
        this->animation = animation;
        update();
    }
}

void GaugeArc::setAnimationStep(double animationStep)
{
    if (this->animationStep != animationStep) {
        this->animationStep = animationStep;
        update();
    }
}

void GaugeArc::setArcColor(const QColor &arcColor)
{
    if (this->arcColor != arcColor) {
        this->arcColor = arcColor;
        update();
    }
}

void GaugeArc::setScaleColor(const QColor &scaleColor)
{
    if (this->scaleColor != scaleColor) {
        this->scaleColor = scaleColor;
        update();
    }
}

void GaugeArc::setScaleNumColor(const QColor &scaleNumColor)
{
    if (this->scaleNumColor != scaleNumColor) {
        this->scaleNumColor = scaleNumColor;
        update();
    }
}

void GaugeArc::setPointerColor(const QColor &pointerColor)
{
    if (this->pointerColor != pointerColor) {
        this->pointerColor = pointerColor;
        update();
    }
}

void GaugeArc::setTextColor(const QColor &textColor)
{
    if (this->textColor != textColor) {
        this->textColor = textColor;
        update();
    }
}

void GaugeArc::setPointerStyle(GaugeArc::PointerStyle pointerStyle)
{
    if (this->pointerStyle != pointerStyle) {
        this->pointerStyle = pointerStyle;
        update();
    }
}
