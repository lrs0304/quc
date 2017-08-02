#pragma execution_character_set("utf-8")

#include "gaugedial.h"
#include "qpainter.h"
#include "qevent.h"
#include "qmath.h"
#include "qdebug.h"

GaugeDial::GaugeDial(QWidget *parent) : QWidget(parent)
{    
    minValue = 0;
    maxValue = 100;
    value = 0;
    precision = 0;

    scaleMajor = 5;
    scaleMinor = 5;
    startAngle = 45;
    endAngle = 45;

    darkColor = QColor(100, 100, 100);
    lightColor = QColor(250, 250, 250);
    textColor = QColor(0, 0, 0);

    showValue = true;
    pointerStyle = PointerStyle_Circle;

    setFont(QFont("Arial", 9));
}

GaugeDial::~GaugeDial()
{

}

void GaugeDial::mousePressEvent(QMouseEvent *e)
{
    pressed = true;
    setPressedValue(e->pos());
}

void GaugeDial::mouseReleaseEvent(QMouseEvent *)
{
    pressed = false;
}

void GaugeDial::mouseMoveEvent(QMouseEvent *e)
{
    if (pressed) {
        setPressedValue(e->pos());
    }
}

void GaugeDial::paintEvent(QPaintEvent *)
{
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    //绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.translate(width / 2, height / 2);    
    painter.scale(side / 200.0, side / 200.0);

    //绘制刻度线
    drawScale(&painter);
    //绘制刻度值
    drawScaleNum(&painter);
    //绘制边界凹凸圆
    drawBorderCircle(&painter);
    //绘制中心圆
    drawCenterCircle(&painter);

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

    //绘制当前值中心背景圆
    drawTextCircle(&painter);
    //绘制当前值
    drawText(&painter);
}

void GaugeDial::drawScale(QPainter *painter)
{
    int radius = 80;
    painter->save();
    painter->setPen(textColor);

    painter->rotate(startAngle);
    int steps = (scaleMajor * scaleMinor);
    double angleStep = (360.0 - startAngle - endAngle) / steps;
    QPen pen = painter->pen();
    pen.setCapStyle(Qt::RoundCap);

    for (int i = 0; i <= steps; i++) {
        if (i % scaleMinor == 0) {
            pen.setWidthF(1.5);
            painter->setPen(pen);
            painter->drawLine(0, radius - 8, 0, radius);
        } else {
            pen.setWidthF(0.5);
            painter->setPen(pen);
            painter->drawLine(0, radius - 8, 0, radius - 3);
        }

        painter->rotate(angleStep);
    }

    painter->restore();
}

void GaugeDial::drawScaleNum(QPainter *painter)
{
    int radius = 90;
    painter->save();
    painter->setPen(textColor);

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

void GaugeDial::drawBorderCircle(QPainter *painter)
{
    int radius = 70;
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient bgGradient(0, -radius, 0, radius);
    bgGradient.setColorAt(0.0, darkColor);
    bgGradient.setColorAt(1.0, lightColor);
    painter->setBrush(bgGradient);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void GaugeDial::drawCenterCircle(QPainter *painter)
{
    int radius = 60;
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient bgGradient(0, -radius, 0, radius);
    bgGradient.setColorAt(0.0, lightColor);
    bgGradient.setColorAt(1.0, darkColor);
    painter->setBrush(bgGradient);

    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void GaugeDial::drawPointerCircle(QPainter *painter)
{
    int radius = 15;
    int offset = 10;
    painter->save();
    painter->setPen(Qt::NoPen);

    painter->rotate(startAngle);
    double degRotate = (360.0 - startAngle - endAngle) / (maxValue - minValue) * (value - minValue);
    painter->rotate(degRotate);

    QLinearGradient bgGradient(0, 0, radius * 2, radius * 2);
    bgGradient.setColorAt(0.0, darkColor);
    bgGradient.setColorAt(1.0, lightColor);
    painter->setBrush(bgGradient);
    painter->drawEllipse(-radius, radius + offset, radius * 2, radius * 2);

    painter->setPen(QPen(darkColor, 2, Qt::SolidLine, Qt::RoundCap));
    painter->drawLine(0, radius * 2 + offset, 0, radius * 2 + 10 + offset);

    painter->restore();
}

void GaugeDial::drawPointerIndicator(QPainter *painter)
{
    int radius = 55;
    painter->save();
    painter->setOpacity(0.8);
    painter->setPen(Qt::NoPen);
    painter->setBrush(darkColor);

    QPolygon pts;
    pts.setPoints(3, -5, 0, 5, 0, 0, radius);

    painter->rotate(startAngle);
    double degRotate = (360.0 - startAngle - endAngle) / (maxValue - minValue) * (value - minValue);
    painter->rotate(degRotate);
    painter->drawConvexPolygon(pts);

    painter->restore();
}

void GaugeDial::drawPointerIndicatorR(QPainter *painter)
{
    int radius = 55;
    painter->save();
    painter->setOpacity(0.6);
    painter->setPen(darkColor);
    painter->setBrush(darkColor);

    QPolygon pts;
    pts.setPoints(3, -5, 0, 5, 0, 0, radius);

    painter->rotate(startAngle);
    double degRotate = (360.0 - startAngle - endAngle) / (maxValue - minValue) * (value - minValue);
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

void GaugeDial::drawPointerTriangle(QPainter *painter)
{
    int radius = 10;
    int offset = 45;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(darkColor);

    QPolygon pts;
    pts.setPoints(3, -radius / 2, offset, radius / 2, offset, 0, radius + offset);

    painter->rotate(startAngle);
    double degRotate = (360.0 - startAngle - endAngle) / (maxValue - minValue) * (value - minValue);
    painter->rotate(degRotate);
    painter->drawConvexPolygon(pts);

    painter->restore();
}

void GaugeDial::drawTextCircle(QPainter *painter)
{
    if (!showValue) {
        return;
    }

    int radius = 15;
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient bgGradient(0, -radius, 0, radius);
    bgGradient.setColorAt(0.0, darkColor);
    bgGradient.setColorAt(1.0, lightColor);
    painter->setBrush(bgGradient);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void GaugeDial::drawText(QPainter *painter)
{
    if (!showValue) {
        return;
    }

    int radius = 100;
    painter->save();
    painter->setPen(textColor);
    painter->setFont(QFont("Arial", 9, QFont::Bold));
    QRectF textRect(-radius, -radius, radius * 2, radius * 2);
    QString strValue = QString("%1").arg((double)value, 0, 'f', precision);
    painter->drawText(textRect, Qt::AlignCenter, strValue);
    painter->restore();
}

void GaugeDial::setPressedValue(QPointF pressedPoint)
{
    //计算总角度
    double length = 360 - startAngle - endAngle;

    //计算最近的刻度
    QPointF point = pressedPoint - rect().center();
    double theta = -atan2(-point.x(), -point.y()) * 180 / M_PI;
    theta = theta + length / 2;

    //计算每一个角度对应值移动多少
    double increment = (maxValue - minValue) / length;
    double currentValue = (theta * increment) + minValue;

    //过滤圆弧外的值
    if (currentValue <= minValue) {
        currentValue = minValue;
    } else if (currentValue >= maxValue) {
        currentValue = maxValue;
    }

    setValue(currentValue);
}

double GaugeDial::getMinValue() const
{
    return this->minValue;
}

double GaugeDial::getMaxValue() const
{
    return this->maxValue;
}

double GaugeDial::getValue() const
{
    return this->value;
}

int GaugeDial::getPrecision() const
{
    return this->precision;
}

int GaugeDial::getScaleMajor() const
{
    return this->scaleMajor;
}

int GaugeDial::getScaleMinor() const
{
    return this->scaleMinor;
}

int GaugeDial::getStartAngle() const
{
    return this->startAngle;
}

int GaugeDial::getEndAngle() const
{
    return this->endAngle;
}

QColor GaugeDial::getDarkColor() const
{
    return this->darkColor;
}

QColor GaugeDial::getLightColor() const
{
    return this->lightColor;
}

QColor GaugeDial::getTextColor() const
{
    return this->textColor;
}

bool GaugeDial::getShowValue() const
{
    return this->showValue;
}

GaugeDial::PointerStyle GaugeDial::getPointerStyle() const
{
    return this->pointerStyle;
}

QSize GaugeDial::sizeHint() const
{
    return QSize(200, 200);
}

QSize GaugeDial::minimumSizeHint() const
{
    return QSize(50, 50);
}

void GaugeDial::setRange(double minValue, double maxValue)
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

void GaugeDial::setRange(int minValue, int maxValue)
{
    setRange((double)minValue, (double)maxValue);
}

void GaugeDial::setMinValue(double minValue)
{
    setRange(minValue, maxValue);
}

void GaugeDial::setMaxValue(double maxValue)
{
    setRange(minValue, maxValue);
}

void GaugeDial::setValue(double value)
{
    //值小于最小值或者值大于最大值或者值和当前值一致则无需处理
    if (value < minValue || value > maxValue || value == this->value) {
        return;
    }

    this->value = value;
    emit valueChanged(value);
    update();
}

void GaugeDial::setValue(int value)
{
    setValue((double)value);
}

void GaugeDial::setPrecision(int precision)
{
    //最大精确度为 3
    if (precision <= 3 && this->precision != precision) {
        this->precision = precision;
        update();
    }
}

void GaugeDial::setScaleMajor(int scaleMajor)
{
    if (this->scaleMajor != scaleMajor) {
        this->scaleMajor = scaleMajor;
        update();
    }
}

void GaugeDial::setScaleMinor(int scaleMinor)
{
    if (this->scaleMinor != scaleMinor) {
        this->scaleMinor = scaleMinor;
        update();
    }
}

void GaugeDial::setStartAngle(int startAngle)
{
    if (this->startAngle != startAngle) {
        this->startAngle = startAngle;
        update();
    }
}

void GaugeDial::setEndAngle(int endAngle)
{
    if (this->endAngle != endAngle) {
        this->endAngle = endAngle;
        update();
    }
}

void GaugeDial::setDarkColor(const QColor &darkColor)
{
    if (this->darkColor != darkColor) {
        this->darkColor = darkColor;
        update();
    }
}

void GaugeDial::setLightColor(const QColor &lightColor)
{
    if (this->lightColor != lightColor) {
        this->lightColor = lightColor;
        update();
    }
}

void GaugeDial::setTextColor(const QColor &textColor)
{
    if (this->textColor != textColor) {
        this->textColor = textColor;
        update();
    }
}

void GaugeDial::setShowValue(bool showValue)
{
    if (this->showValue != showValue) {
        this->showValue = showValue;
        update();
    }
}

void GaugeDial::setPointerStyle(GaugeDial::PointerStyle pointerStyle)
{
    if (this->pointerStyle != pointerStyle) {
        this->pointerStyle = pointerStyle;
        update();
    }
}
