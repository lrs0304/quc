#pragma execution_character_set("utf-8")

#include "gaugesimple.h"
#include "qpainter.h"
#include "qmath.h"
#include "qtimer.h"
#include "qdebug.h"

GaugeSimple::GaugeSimple(QWidget *parent) : QWidget(parent)
{
    minValue = 0;
    maxValue = 100;
    value = 0;

    scaleMajor = 10;
    scaleMinor = 10;
    startAngle = 45;
    endAngle = 45;

    animation = false;
    animationStep = 1.1;

    usedColor = QColor(100, 184, 255);
    freeColor = QColor(100, 100, 100);

    scaleColor = QColor(50, 50, 50);
    pointerColor = QColor(255, 107, 107);
    textColor = QColor(250, 250, 250);
    titleColor = QColor(50, 50, 50);

    title = "";

    showOverlay = false;
    overlayColor = QColor(255, 255, 255, 60);

    pointerStyle = PointerStyle_Indicator;

    reverse = false;
    currentValue = 0;
    timer = new QTimer(this);
    timer->setInterval(10);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateValue()));

    setFont(QFont("Arial", 10));
}

GaugeSimple::~GaugeSimple()
{
    if (timer->isActive()) {
        timer->stop();
    }
}

void GaugeSimple::paintEvent(QPaintEvent *)
{
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    //绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.translate(width / 2, height / 2);
    painter.scale(side / 200.0, side / 200.0);

    //绘制当前值及剩余值圆弧
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
    //绘制标题
    drawTitle(&painter);
    //绘制遮罩层
    drawOverlay(&painter);
}

void GaugeSimple::drawArc(QPainter *painter)
{
    int radius = 99;
    painter->save();
    painter->setBrush(Qt::NoBrush);

    //绘制圆弧方法绘制圆环
    int penWidth = 10;
    QRectF rect(-radius + penWidth / 2, -radius + penWidth / 2, radius * 2 - penWidth, radius * 2 - penWidth);
    //可以自行修改画笔的后三个参数,形成各种各样的效果,例如Qt::FlatCap改为Qt::FlatCap可以产生圆角效果
    QPen pen(usedColor, penWidth, Qt::SolidLine, Qt::FlatCap, Qt::MPenJoinStyle);

    //计算总范围角度,当前值范围角度,剩余值范围角度
    double angleAll = 360.0 - startAngle - endAngle;
    double angleCurrent = angleAll * ((currentValue - minValue) / (maxValue - minValue));
    double angleOther = angleAll - angleCurrent;

    //绘制当前值饼圆
    painter->setPen(pen);
    painter->drawArc(rect, (270 - startAngle - angleCurrent) * 16, angleCurrent * 16);

    //绘制剩余值饼圆
    pen.setColor(freeColor);
    painter->setPen(pen);
    painter->drawArc(rect, (270 - startAngle - angleCurrent - angleOther) * 16, angleOther * 16);

    painter->restore();
}

void GaugeSimple::drawScale(QPainter *painter)
{
    int radius = 60;
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

void GaugeSimple::drawScaleNum(QPainter *painter)
{
    int radius = 75;
    painter->save();
    painter->setPen(scaleColor);

    double startRad = (360 - startAngle - 90) * (M_PI / 180);
    double deltaRad = (360 - startAngle - endAngle) * (M_PI / 180) / scaleMajor;

    for (int i = 0; i <= scaleMajor; i++) {
        double sina = sin(startRad - i * deltaRad);
        double cosa = cos(startRad - i * deltaRad);
        double value = 1.0 * i * ((maxValue - minValue) / scaleMajor) + minValue;

        QString strValue = QString("%1").arg(value);
        double textWidth = fontMetrics().width(strValue);
        double textHeight = fontMetrics().height();
        int x = radius * cosa - textWidth / 2;
        int y = -radius * sina + textHeight / 4;
        painter->drawText(x, y, strValue);
    }

    painter->restore();
}

void GaugeSimple::drawPointerCircle(QPainter *painter)
{
    int radius = 12;
    int offset = 20;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(pointerColor);

    painter->rotate(startAngle);
    double degRotate = (360.0 - startAngle - endAngle) / (maxValue - minValue) * (currentValue - minValue);
    painter->rotate(degRotate);
    painter->drawEllipse(-radius, radius + offset, radius * 2, radius * 2);

    painter->restore();
}

void GaugeSimple::drawPointerIndicator(QPainter *painter)
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

void GaugeSimple::drawPointerIndicatorR(QPainter *painter)
{
    int radius = 75;
    painter->save();
    painter->setOpacity(0.6);
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

void GaugeSimple::drawPointerTriangle(QPainter *painter)
{
    int radius = 10;
    int offset = 45;
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

void GaugeSimple::drawRoundCircle(QPainter *painter)
{
    int radius = 25;
    painter->save();
    painter->setOpacity(0.6);
    painter->setPen(Qt::NoPen);
    painter->setBrush(pointerColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void GaugeSimple::drawCenterCircle(QPainter *painter)
{
    int radius = 20;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(pointerColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void GaugeSimple::drawText(QPainter *painter)
{
    int radius = 100;
    painter->save();
    painter->setPen(textColor);
    painter->setFont(QFont("Arial", 11));

    QRectF textRect(-radius, -radius, radius * 2, radius * 2);
    QString strValue = QString::number(currentValue, 'f', 1);
    painter->drawText(textRect, Qt::AlignCenter, strValue);

    painter->restore();
}

void GaugeSimple::drawTitle(QPainter *painter)
{
    if (title.isEmpty()) {
        return;
    }

    int radius = 100;
    painter->save();
    painter->setPen(titleColor);
    painter->setFont(QFont("Arial", 10));

    QRectF titleRect(-radius, 0, radius * 2, radius);
    painter->drawText(titleRect, Qt::AlignCenter, title);

    painter->restore();
}

void GaugeSimple::drawOverlay(QPainter *painter)
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

void GaugeSimple::updateValue()
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

double GaugeSimple::getMinValue() const
{
    return this->minValue;
}

double GaugeSimple::getMaxValue() const
{
    return this->maxValue;
}

double GaugeSimple::getValue() const
{
    return this->value;
}

int GaugeSimple::getScaleMajor() const
{
    return this->scaleMajor;
}

int GaugeSimple::getScaleMinor() const
{
    return this->scaleMinor;
}

int GaugeSimple::getStartAngle() const
{
    return this->startAngle;
}

int GaugeSimple::getEndAngle() const
{
    return this->endAngle;
}

bool GaugeSimple::getAnimation() const
{
    return this->animation;
}

double GaugeSimple::getAnimationStep() const
{
    return this->animationStep;
}

QColor GaugeSimple::getUsedColor() const
{
    return this->usedColor;
}

QColor GaugeSimple::getFreeColor() const
{
    return this->freeColor;
}

QColor GaugeSimple::getScaleColor() const
{
    return this->scaleColor;
}

QColor GaugeSimple::getPointerColor() const
{
    return this->pointerColor;
}

QColor GaugeSimple::getTextColor() const
{
    return this->textColor;
}

QColor GaugeSimple::getTitleColor() const
{
    return this->titleColor;
}

QString GaugeSimple::getTitle() const
{
    return this->title;
}

bool GaugeSimple::getShowOverlay() const
{
    return this->showOverlay;
}

QColor GaugeSimple::getOverlayColor() const
{
    return this->overlayColor;
}

GaugeSimple::PointerStyle GaugeSimple::getPointerStyle() const
{
    return this->pointerStyle;
}

QSize GaugeSimple::sizeHint() const
{
    return QSize(200, 200);
}

QSize GaugeSimple::minimumSizeHint() const
{
    return QSize(50, 50);
}

void GaugeSimple::setRange(double minValue, double maxValue)
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

void GaugeSimple::setMinValue(double minValue)
{
    setRange(minValue, maxValue);
}

void GaugeSimple::setMaxValue(double maxValue)
{
    setRange(minValue, maxValue);
}

void GaugeSimple::setValue(double value)
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

void GaugeSimple::setScaleMajor(int scaleMajor)
{
    if (this->scaleMajor != scaleMajor) {
        this->scaleMajor = scaleMajor;
        update();
    }
}

void GaugeSimple::setScaleMinor(int scaleMinor)
{
    if (this->scaleMinor != scaleMinor) {
        this->scaleMinor = scaleMinor;
        update();
    }
}

void GaugeSimple::setStartAngle(int startAngle)
{
    if (this->startAngle != startAngle) {
        this->startAngle = startAngle;
        update();
    }
}

void GaugeSimple::setEndAngle(int endAngle)
{
    if (this->endAngle != endAngle) {
        this->endAngle = endAngle;
        update();
    }
}

void GaugeSimple::setAnimation(bool animation)
{
    if (this->animation != animation) {
        this->animation = animation;
        update();
    }
}

void GaugeSimple::setAnimationStep(double animationStep)
{
    if (this->animationStep != animationStep) {
        this->animationStep = animationStep;
        update();
    }
}

void GaugeSimple::setUsedColor(const QColor &usedColor)
{
    if (this->usedColor != usedColor) {
        this->usedColor = usedColor;
        update();
    }
}

void GaugeSimple::setFreeColor(const QColor &freeColor)
{
    if (this->freeColor != freeColor) {
        this->freeColor = freeColor;
        update();
    }
}

void GaugeSimple::setScaleColor(const QColor &scaleColor)
{
    if (this->scaleColor != scaleColor) {
        this->scaleColor = scaleColor;
        update();
    }
}

void GaugeSimple::setPointerColor(const QColor &pointerColor)
{
    if (this->pointerColor != pointerColor) {
        this->pointerColor = pointerColor;
        update();
    }
}

void GaugeSimple::setTextColor(const QColor &textColor)
{
    if (this->textColor != textColor) {
        this->textColor = textColor;
        update();
    }
}

void GaugeSimple::setTitleColor(const QColor &titleColor)
{
    if (this->titleColor != titleColor) {
        this->titleColor = titleColor;
        update();
    }
}

void GaugeSimple::setTitle(const QString &title)
{
    if (this->title != title) {
        this->title = title;
        update();
    }
}

void GaugeSimple::setShowOverlay(bool showOverlay)
{
    if (this->showOverlay != showOverlay) {
        this->showOverlay = showOverlay;
        update();
    }
}

void GaugeSimple::setOverlayColor(const QColor &overlayColor)
{
    if (this->overlayColor != overlayColor) {
        this->overlayColor = overlayColor;
        update();
    }
}

void GaugeSimple::setPointerStyle(GaugeSimple::PointerStyle pointerStyle)
{
    if (this->pointerStyle != pointerStyle) {
        this->pointerStyle = pointerStyle;
        update();
    }
}
