#pragma execution_character_set("utf-8")

#include "gaugespeed.h"
#include "qpainter.h"
#include "qmath.h"
#include "qtimer.h"
#include "qlcdnumber.h"
#include "qdebug.h"

GaugeSpeed::GaugeSpeed(QWidget *parent) : QWidget(parent)
{    
    minValue = 0;
    maxValue = 100;
    value = 0;
    precision = 2;

    scaleMajor = 8;
    scaleMinor = 1;
    startAngle = 50;
    endAngle = 50;

    animation = false;
    animationStep = 0.5;

    ringWidth = 10;
    ringStartPercent = 25;
    ringMidPercent = 50;
    ringEndPercent = 25;

    ringColorStart = QColor(2, 242, 177);
    ringColorMid = QColor(45, 196, 248);
    ringColorEnd = QColor(254, 68, 138);

    pointerColor = QColor(178, 221, 253);
    textColor = QColor(50, 50, 50);

    reverse = false;
    currentValue = 0;
    timer = new QTimer(this);
    timer->setInterval(10);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateValue()));

    //显示数码管
    lcd = new QLCDNumber(5, this);
    lcd->setSegmentStyle(QLCDNumber::Flat);
    lcd->setFrameShape(QFrame::NoFrame);

    QPalette pal = lcd->palette();
    pal.setColor(QPalette::Foreground, textColor);
    lcd->setPalette(pal);

    setFont(QFont("Arial", 7));
}

GaugeSpeed::~GaugeSpeed()
{
    if (timer->isActive()) {
        timer->stop();
    }
}

void GaugeSpeed::resizeEvent(QResizeEvent *)
{
    int width = this->width();
    int height = this->height();
    int lcdWidth = width / 4;
    int lcdHeight = height / 9;
    lcd->setGeometry((width - lcdWidth) / 2, height - (2.2 * lcdHeight), lcdWidth, lcdHeight);
}

void GaugeSpeed::paintEvent(QPaintEvent *)
{
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    //绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.translate(width / 2, height / 2);    
    painter.scale(side / 200.0, side / 200.0);

    //绘制圆环
    drawRing(&painter);

    //绘制刻度线
    drawScale(&painter);

    //绘制刻度值
    drawScaleNum(&painter);

    //根据指示器形状绘制指示器
    drawPointer(&painter);

    //绘制当前值
    drawText(&painter);
}

void GaugeSpeed::drawRing(QPainter *painter)
{
    int radius = 100;
    painter->save();
    QPen pen = painter->pen();
    pen.setCapStyle(Qt::FlatCap);
    pen.setWidthF(ringWidth);
    radius = radius - ringWidth;

    QRectF rect = QRectF(-radius, -radius, radius * 2, radius * 2);

    //计算总范围角度,根据占比例自动计算三色圆环范围角度
    double angleAll = 360.0 - startAngle - endAngle;
    double angleStart = angleAll * (double)ringStartPercent / 100;
    double angleMid = angleAll * (double)ringMidPercent / 100;
    double angleEnd = angleAll * (double)ringEndPercent / 100;

    //绘制第一圆环
    pen.setColor(ringColorStart);
    painter->setPen(pen);
    painter->drawArc(rect, (270 - startAngle - angleStart) * 16, angleStart * 16);

    //绘制第二圆环
    pen.setColor(ringColorMid);
    painter->setPen(pen);
    painter->drawArc(rect, (270 - startAngle - angleStart - angleMid) * 16, angleMid * 16);

    //绘制第三圆环
    pen.setColor(ringColorEnd);
    painter->setPen(pen);
    painter->drawArc(rect, (270 - startAngle - angleStart - angleMid - angleEnd) * 16, angleEnd * 16);

    painter->restore();
}

void GaugeSpeed::drawScale(QPainter *painter)
{
    int radius = 94;
    painter->save();
    QPen pen = painter->pen();
    pen.setColor(textColor);
    pen.setCapStyle(Qt::RoundCap);

    painter->rotate(startAngle);
    int steps = (scaleMajor * scaleMinor);
    double angleStep = (360.0 - startAngle - endAngle) / steps;

    //计算圆环对应大刻度范围索引
    int indexStart = steps * (double)ringStartPercent / 100 + 1;
    int indexMid = steps * (double)ringMidPercent / 100 - 1;
    int indexEnd = steps * (double)ringEndPercent / 100 + 1;
    int index = 0;

    for (int i = 0; i <= steps; i++) {
        if (i % scaleMinor == 0) {
            //根据所在圆环范围切换颜色
            if (index < indexStart) {
                pen.setColor(ringColorStart);
            } else if (index < (indexStart + indexMid)) {
                pen.setColor(ringColorMid);
            } else if (index < (indexStart + indexMid + indexEnd)) {
                pen.setColor(ringColorEnd);
            }

            index++;

            pen.setWidthF(1.5);
            painter->setPen(pen);
            painter->drawLine(0, radius - 13, 0, radius);
        } else {
            pen.setWidthF(0.5);
            painter->setPen(pen);
            painter->drawLine(0, radius - 5, 0, radius);
        }

        painter->rotate(angleStep);
    }

    painter->restore();
}

void GaugeSpeed::drawScaleNum(QPainter *painter)
{
    int radius = 70;
    painter->save();
    painter->setPen(textColor);

    double startRad = (360 - startAngle - 90) * (M_PI / 180);
    double deltaRad = (360 - startAngle - endAngle) * (M_PI / 180) / scaleMajor;

    for (int i = 0; i <= scaleMajor; i++) {
        double sina = sin(startRad - i * deltaRad);
        double cosa = cos(startRad - i * deltaRad);
        double value = 1.0 * i * ((maxValue - minValue) / scaleMajor) + minValue;

        QString strValue = QString("%1M").arg((double)value, 0, 'f', 0);
        double textWidth = fontMetrics().width(strValue);
        double textHeight = fontMetrics().height();
        int x = radius * cosa - textWidth / 2;
        int y = -radius * sina + textHeight / 4;
        painter->drawText(x, y, strValue);
    }

    painter->restore();
}

void GaugeSpeed::drawPointer(QPainter *painter)
{
    int radius = 62;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(pointerColor);

    QPolygon pts;
    pts.setPoints(4, -5, 0, 0, -8, 5, 0, 0, radius);

    painter->rotate(startAngle);
    double degRotate = (360.0 - startAngle - endAngle) / (maxValue - minValue) * (currentValue - minValue);
    painter->rotate(degRotate);
    painter->drawConvexPolygon(pts);

    painter->restore();
}

void GaugeSpeed::drawText(QPainter *painter)
{
    int radius = 100;
    painter->save();
    painter->setPen(textColor);

    QRectF unitRect(-radius, radius / 3, radius * 2, radius / 4);
    QString strUnit = QString("%1").arg("Mbps");
    painter->setFont(QFont("Arial", 5));
    painter->drawText(unitRect, Qt::AlignCenter, strUnit);

    QRectF textRect(-radius, radius / 2.3, radius * 2, radius / 3);
    QString strValue = QString("%1").arg((double)currentValue, 0, 'f', precision);
    strValue = QString("%1").arg(strValue, 5, QLatin1Char('0'));
    painter->setFont(QFont("Arial", 15));

#if 0
    lcd->setVisible(false);
    painter->drawText(textRect, Qt::AlignCenter, strValue);
#else
    lcd->display(strValue);
#endif

    painter->restore();
}

void GaugeSpeed::updateValue()
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

double GaugeSpeed::getMinValue() const
{
    return this->minValue;
}

double GaugeSpeed::getMaxValue() const
{
    return this->maxValue;
}

double GaugeSpeed::getValue() const
{
    return this->value;
}

int GaugeSpeed::getPrecision() const
{
    return this->precision;
}

int GaugeSpeed::getScaleMajor() const
{
    return this->scaleMajor;
}

int GaugeSpeed::getScaleMinor() const
{
    return this->scaleMinor;
}

int GaugeSpeed::getStartAngle() const
{
    return this->startAngle;
}

int GaugeSpeed::getEndAngle() const
{
    return this->endAngle;
}

bool GaugeSpeed::getAnimation() const
{
    return this->animation;
}

double GaugeSpeed::getAnimationStep() const
{
    return this->animationStep;
}

int GaugeSpeed::getRingWidth() const
{
    return this->ringWidth;
}

int GaugeSpeed::getRingStartPercent() const
{
    return this->ringStartPercent;
}

int GaugeSpeed::getRingMidPercent() const
{
    return this->ringMidPercent;
}

int GaugeSpeed::getRingEndPercent() const
{
    return this->ringEndPercent;
}

QColor GaugeSpeed::getRingColorStart() const
{
    return this->ringColorStart;
}

QColor GaugeSpeed::getRingColorMid() const
{
    return this->ringColorMid;
}

QColor GaugeSpeed::getRingColorEnd() const
{
    return this->ringColorEnd;
}

QColor GaugeSpeed::getPointerColor() const
{
    return this->pointerColor;
}

QColor GaugeSpeed::getTextColor() const
{
    return this->textColor;
}

QSize GaugeSpeed::sizeHint() const
{
    return QSize(200, 200);
}

QSize GaugeSpeed::minimumSizeHint() const
{
    return QSize(50, 50);
}

void GaugeSpeed::setRange(double minValue, double maxValue)
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

void GaugeSpeed::setRange(int minValue, int maxValue)
{
    setRange((double)minValue, (double)maxValue);
}

void GaugeSpeed::setMinValue(double minValue)
{
    setRange(minValue, maxValue);
}

void GaugeSpeed::setMaxValue(double maxValue)
{
    setRange(minValue, maxValue);
}

void GaugeSpeed::setValue(double value)
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

void GaugeSpeed::setValue(int value)
{
    setValue((double)value);
}

void GaugeSpeed::setPrecision(int precision)
{
    //最大精确度为 3
    if (precision <= 3 && this->precision != precision) {
        this->precision = precision;
        update();
    }
}

void GaugeSpeed::setScaleMajor(int scaleMajor)
{
    if (this->scaleMajor != scaleMajor) {
        this->scaleMajor = scaleMajor;
        update();
    }
}

void GaugeSpeed::setScaleMinor(int scaleMinor)
{
    if (this->scaleMinor != scaleMinor) {
        this->scaleMinor = scaleMinor;
        update();
    }
}

void GaugeSpeed::setStartAngle(int startAngle)
{
    if (this->startAngle != startAngle) {
        this->startAngle = startAngle;
        update();
    }
}

void GaugeSpeed::setEndAngle(int endAngle)
{
    if (this->endAngle != endAngle) {
        this->endAngle = endAngle;
        update();
    }
}

void GaugeSpeed::setAnimation(bool animation)
{
    if (this->animation != animation) {
        this->animation = animation;
        update();
    }
}

void GaugeSpeed::setAnimationStep(double animationStep)
{
    if (this->animationStep != animationStep) {
        this->animationStep = animationStep;
        update();
    }
}

void GaugeSpeed::setRingWidth(int ringWidth)
{
    if (this->ringWidth != ringWidth) {
        this->ringWidth = ringWidth;
        update();
    }
}

void GaugeSpeed::setRingStartPercent(int ringStartPercent)
{
    //所占比例不能小于1 或者总比例不能大于100
    if (ringStartPercent < 1 || (ringStartPercent + ringMidPercent + ringEndPercent) > 100) {
        return;
    }

    if (this->ringStartPercent != ringStartPercent) {
        this->ringStartPercent = ringStartPercent;
        update();
    }
}

void GaugeSpeed::setRingMidPercent(int ringMidPercent)
{
    //所占比例不能小于1 或者总比例不能大于100
    if (ringStartPercent < 1 || (ringStartPercent + ringMidPercent + ringEndPercent) > 100) {
        return;
    }

    if (this->ringMidPercent != ringMidPercent) {
        this->ringMidPercent = ringMidPercent;
        update();
    }
}

void GaugeSpeed::setRingEndPercent(int ringEndPercent)
{
    //所占比例不能小于1 或者总比例不能大于100
    if (ringStartPercent < 1 || (ringStartPercent + ringMidPercent + ringEndPercent) > 100) {
        return;
    }

    if (this->ringEndPercent != ringEndPercent) {
        this->ringEndPercent = ringEndPercent;
        update();
    }
}

void GaugeSpeed::setRingColorStart(const QColor &ringColorStart)
{
    if (this->ringColorStart != ringColorStart) {
        this->ringColorStart = ringColorStart;
        update();
    }
}

void GaugeSpeed::setRingColorMid(const QColor &ringColorMid)
{
    if (this->ringColorMid != ringColorMid) {
        this->ringColorMid = ringColorMid;
        update();
    }
}

void GaugeSpeed::setRingColorEnd(const QColor &ringColorEnd)
{
    if (this->ringColorEnd != ringColorEnd) {
        this->ringColorEnd = ringColorEnd;
        update();
    }
}

void GaugeSpeed::setPointerColor(const QColor &pointerColor)
{
    if (this->pointerColor != pointerColor) {
        this->pointerColor = pointerColor;
        update();
    }
}

void GaugeSpeed::setTextColor(const QColor &textColor)
{
    if (this->textColor != textColor) {
        QPalette pal = lcd->palette();
        pal.setColor(QPalette::Foreground, textColor);
        lcd->setPalette(pal);        

        this->textColor = textColor;
        update();
    }
}
