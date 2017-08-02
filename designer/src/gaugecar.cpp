#pragma execution_character_set("utf-8")

#include "gaugecar.h"
#include "qpainter.h"
#include "qmath.h"
#include "qtimer.h"
#include "qdebug.h"

GaugeCar::GaugeCar(QWidget *parent) : QWidget(parent)
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

    outerCircleColor = QColor(80, 80, 80);
    innerCircleColor = QColor(60, 60, 60);

    pieColorStart = QColor(24, 189, 155);
    pieColorMid = QColor(218, 218, 0);
    pieColorEnd = QColor(255, 107, 107);

    coverCircleColor = QColor(100, 100, 100);
    scaleColor = QColor(255, 255, 255);
    pointerColor = QColor(255, 107, 107);
    centerCircleColor = QColor(200, 200, 200);
    textColor = QColor(0, 0, 0);

    showOverlay = false;
    overlayColor = QColor(255, 255, 255, 60);

    pieStyle = PieStyle_Three;
    pointerStyle = PointerStyle_Indicator;

    reverse = false;
    currentValue = 0;
    timer = new QTimer(this);
    timer->setInterval(10);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateValue()));

    setFont(QFont("Arial", 7));
}

GaugeCar::~GaugeCar()
{
    if (timer->isActive()) {
        timer->stop();
    }
}

void GaugeCar::paintEvent(QPaintEvent *)
{
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    //绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.translate(width / 2, height / 2);    
    painter.scale(side / 200.0, side / 200.0);

    //绘制外圆
    drawOuterCircle(&painter);
    //绘制内圆
    drawInnerCircle(&painter);
    //绘制饼圆
    drawColorPie(&painter);
    //绘制覆盖圆 用以遮住饼圆多余部分
    drawCoverCircle(&painter);
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
    //绘制遮罩层
    drawOverlay(&painter);
}

void GaugeCar::drawOuterCircle(QPainter *painter)
{
    int radius = 99;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(outerCircleColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void GaugeCar::drawInnerCircle(QPainter *painter)
{
    int radius = 90;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(innerCircleColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void GaugeCar::drawColorPie(QPainter *painter)
{
    int radius = 60;
    painter->save();
    painter->setPen(Qt::NoPen);

    QRectF rect(-radius, -radius, radius * 2, radius * 2);

    if (pieStyle == PieStyle_Three) {
        //计算总范围角度,根据占比例自动计算三色圆环范围角度
        double angleAll = 360.0 - startAngle - endAngle;
        double angleStart = angleAll * 0.7;
        double angleMid = angleAll * 0.15;
        double angleEnd = angleAll * 0.15;

        //绘制开始饼圆
        painter->setBrush(pieColorStart);
        painter->drawPie(rect, (270 - startAngle - angleStart) * 16, angleStart * 16);

        //绘制中间饼圆
        painter->setBrush(pieColorMid);
        painter->drawPie(rect, (270 - startAngle - angleStart - angleMid) * 16, angleMid * 16);

        //绘制结束饼圆
        painter->setBrush(pieColorEnd);
        painter->drawPie(rect, (270 - startAngle - angleStart - angleMid - angleEnd) * 16, angleEnd * 16);
    } else if (pieStyle == PieStyle_Current) {
        //计算总范围角度,当前值范围角度,剩余值范围角度
        double angleAll = 360.0 - startAngle - endAngle;
        double angleCurrent = angleAll * ((currentValue - minValue) / (maxValue - minValue));
        double angleOther = angleAll - angleCurrent;

        //绘制当前值饼圆
        painter->setBrush(pieColorStart);
        painter->drawPie(rect, (270 - startAngle - angleCurrent) * 16, angleCurrent * 16);

        //绘制剩余值饼圆
        painter->setBrush(pieColorEnd);
        painter->drawPie(rect, (270 - startAngle - angleCurrent - angleOther) * 16, angleOther * 16);
    }

    painter->restore();
}

void GaugeCar::drawCoverCircle(QPainter *painter)
{
    int radius = 50;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(coverCircleColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void GaugeCar::drawScale(QPainter *painter)
{
    int radius = 72;
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
            painter->drawLine(0, radius - 10, 0, radius);
        } else {
            pen.setWidthF(0.5);
            painter->setPen(pen);
            painter->drawLine(0, radius - 5, 0, radius);
        }

        painter->rotate(angleStep);
    }

    painter->restore();
}

void GaugeCar::drawScaleNum(QPainter *painter)
{
    int radius = 82;
    painter->save();
    painter->setPen(scaleColor);

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

void GaugeCar::drawPointerCircle(QPainter *painter)
{
    int radius = 12;
    int offset = 10;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(pointerColor);

    painter->rotate(startAngle);
    double degRotate = (360.0 - startAngle - endAngle) / (maxValue - minValue) * (currentValue - minValue);
    painter->rotate(degRotate);
    painter->drawEllipse(-radius, radius + offset, radius * 2, radius * 2);

    painter->restore();
}

void GaugeCar::drawPointerIndicator(QPainter *painter)
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

void GaugeCar::drawPointerIndicatorR(QPainter *painter)
{
    int radius = 75;
    painter->save();
    painter->setOpacity(1.0);
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

void GaugeCar::drawPointerTriangle(QPainter *painter)
{
    int radius = 10;
    int offset = 38;
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

void GaugeCar::drawRoundCircle(QPainter *painter)
{
    int radius = 18;
    painter->save();
    painter->setOpacity(0.8);
    painter->setPen(Qt::NoPen);
    painter->setBrush(pointerColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void GaugeCar::drawCenterCircle(QPainter *painter)
{
    int radius = 15;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(centerCircleColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void GaugeCar::drawText(QPainter *painter)
{
    int radius = 100;
    painter->save();
    painter->setPen(textColor);
    painter->setFont(QFont("Arial", 9));

    QRectF textRect(-radius, -radius, radius * 2, radius * 2);
    QString strValue = QString("%1").arg((double)currentValue, 0, 'f', precision);
    painter->drawText(textRect, Qt::AlignCenter, strValue);

    painter->restore();
}

void GaugeCar::drawOverlay(QPainter *painter)
{
    if (!showOverlay) {
        return;
    }

    int radius = 90;
    painter->save();
    painter->setPen(Qt::NoPen);

    QPainterPath smallCircle;
    QPainterPath bigCircle;
    radius -= 1;
    smallCircle.addEllipse(-radius, -radius, radius * 2, radius * 2);
    radius *= 2;
    bigCircle.addEllipse(-radius, -radius + 140, radius * 2, radius * 2);

    //高光的形状为小圆扣掉大圆的部分
    QPainterPath highlight = smallCircle - bigCircle;

    QLinearGradient linearGradient(0, -radius / 2, 0, 0);
    overlayColor.setAlpha(100);
    linearGradient.setColorAt(0.0, overlayColor);
    overlayColor.setAlpha(30);
    linearGradient.setColorAt(1.0, overlayColor);
    painter->setBrush(linearGradient);
    painter->rotate(-20);
    painter->drawPath(highlight);

    painter->restore();
}

void GaugeCar::updateValue()
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

double GaugeCar::getMinValue() const
{
    return this->minValue;
}

double GaugeCar::getMaxValue() const
{
    return this->maxValue;
}

double GaugeCar::getValue() const
{
    return this->value;
}

int GaugeCar::getPrecision() const
{
    return this->precision;
}

int GaugeCar::getScaleMajor() const
{
    return this->scaleMajor;
}

int GaugeCar::getScaleMinor() const
{
    return this->scaleMinor;
}

int GaugeCar::getStartAngle() const
{
    return this->startAngle;
}

int GaugeCar::getEndAngle() const
{
    return this->endAngle;
}

bool GaugeCar::getAnimation() const
{
    return this->animation;
}

double GaugeCar::getAnimationStep() const
{
    return this->animationStep;
}

QColor GaugeCar::getOuterCircleColor() const
{
    return this->outerCircleColor;
}

QColor GaugeCar::getInnerCircleColor() const
{
    return this->innerCircleColor;
}

QColor GaugeCar::getPieColorStart() const
{
    return this->pieColorStart;
}

QColor GaugeCar::getPieColorMid() const
{
    return this->pieColorMid;
}

QColor GaugeCar::getPieColorEnd() const
{
    return this->pieColorEnd;
}

QColor GaugeCar::getCoverCircleColor() const
{
    return this->coverCircleColor;
}

QColor GaugeCar::getScaleColor() const
{
    return this->scaleColor;
}

QColor GaugeCar::getPointerColor() const
{
    return this->pointerColor;
}

QColor GaugeCar::getCenterCircleColor() const
{
    return this->centerCircleColor;
}

QColor GaugeCar::getTextColor() const
{
    return this->textColor;
}

bool GaugeCar::getShowOverlay() const
{
    return this->showOverlay;
}

QColor GaugeCar::getOverlayColor() const
{
    return this->overlayColor;
}

GaugeCar::PieStyle GaugeCar::getPieStyle() const
{
    return this->pieStyle;
}

GaugeCar::PointerStyle GaugeCar::getPointerStyle() const
{
    return this->pointerStyle;
}

QSize GaugeCar::sizeHint() const
{
    return QSize(200, 200);
}

QSize GaugeCar::minimumSizeHint() const
{
    return QSize(50, 50);
}

void GaugeCar::setRange(double minValue, double maxValue)
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

void GaugeCar::setRange(int minValue, int maxValue)
{
    setRange((double)minValue, (double)maxValue);
}

void GaugeCar::setMinValue(double minValue)
{
    setRange(minValue, maxValue);
}

void GaugeCar::setMaxValue(double maxValue)
{
    setRange(minValue, maxValue);
}

void GaugeCar::setValue(double value)
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

void GaugeCar::setValue(int value)
{
    setValue((double)value);
}

void GaugeCar::setPrecision(int precision)
{
    //最大精确度为 3
    if (precision <= 3 && this->precision != precision) {
        this->precision = precision;
        update();
    }
}

void GaugeCar::setScaleMajor(int scaleMajor)
{
    if (this->scaleMajor != scaleMajor) {
        this->scaleMajor = scaleMajor;
        update();
    }
}

void GaugeCar::setScaleMinor(int scaleMinor)
{
    if (this->scaleMinor != scaleMinor) {
        this->scaleMinor = scaleMinor;
        update();
    }
}

void GaugeCar::setStartAngle(int startAngle)
{
    if (this->startAngle != startAngle) {
        this->startAngle = startAngle;
        update();
    }
}

void GaugeCar::setEndAngle(int endAngle)
{
    if (this->endAngle != endAngle) {
        this->endAngle = endAngle;
        update();
    }
}

void GaugeCar::setAnimation(bool animation)
{
    if (this->animation != animation) {
        this->animation = animation;
        update();
    }
}

void GaugeCar::setAnimationStep(double animationStep)
{
    if (this->animationStep != animationStep) {
        this->animationStep = animationStep;
        update();
    }
}

void GaugeCar::setOuterCircleColor(const QColor &outerCircleColor)
{
    if (this->outerCircleColor != outerCircleColor) {
        this->outerCircleColor = outerCircleColor;
        update();
    }
}

void GaugeCar::setInnerCircleColor(const QColor &innerCircleColor)
{
    if (this->innerCircleColor != innerCircleColor) {
        this->innerCircleColor = innerCircleColor;
        update();
    }
}

void GaugeCar::setPieColorStart(const QColor &pieColorStart)
{
    if (this->pieColorStart != pieColorStart) {
        this->pieColorStart = pieColorStart;
        update();
    }
}

void GaugeCar::setPieColorMid(const QColor &pieColorMid)
{
    if (this->pieColorMid != pieColorMid) {
        this->pieColorMid = pieColorMid;
        update();
    }
}

void GaugeCar::setPieColorEnd(const QColor &pieColorEnd)
{
    if (this->pieColorEnd != pieColorEnd) {
        this->pieColorEnd = pieColorEnd;
        update();
    }
}

void GaugeCar::setCoverCircleColor(const QColor &coverCircleColor)
{
    if (this->coverCircleColor != coverCircleColor) {
        this->coverCircleColor = coverCircleColor;
        update();
    }
}

void GaugeCar::setScaleColor(const QColor &scaleColor)
{
    if (this->scaleColor != scaleColor) {
        this->scaleColor = scaleColor;
        update();
    }
}

void GaugeCar::setPointerColor(const QColor &pointerColor)
{
    if (this->pointerColor != pointerColor) {
        this->pointerColor = pointerColor;
        update();
    }
}

void GaugeCar::setCenterCircleColor(const QColor &centerCircleColor)
{
    if (this->centerCircleColor != centerCircleColor) {
        this->centerCircleColor = centerCircleColor;
        update();
    }
}

void GaugeCar::setTextColor(const QColor &textColor)
{
    if (this->textColor != textColor) {
        this->textColor = textColor;
        update();
    }
}

void GaugeCar::setShowOverlay(bool showOverlay)
{
    if (this->showOverlay != showOverlay) {
        this->showOverlay = showOverlay;
        update();
    }
}

void GaugeCar::setOverlayColor(const QColor &overlayColor)
{
    if (this->overlayColor != overlayColor) {
        this->overlayColor = overlayColor;
        update();
    }
}

void GaugeCar::setPieStyle(GaugeCar::PieStyle pieStyle)
{
    if (this->pieStyle != pieStyle) {
        this->pieStyle = pieStyle;
        update();
    }
}

void GaugeCar::setPointerStyle(GaugeCar::PointerStyle pointerStyle)
{
    if (this->pointerStyle != pointerStyle) {
        this->pointerStyle = pointerStyle;
        update();
    }
}
