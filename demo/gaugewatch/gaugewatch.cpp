#pragma execution_character_set("utf-8")

#include "gaugewatch.h"
#include "qpainter.h"
#include "qmath.h"
#include "qtimer.h"
#include "qdebug.h"

GaugeWatch::GaugeWatch(QWidget *parent) : QWidget(parent)
{    
    minValue = 0;
    maxValue = 100;
    value = 0;
    precision = 0;

    unit = "km/h";
    title = "时速表";

    scaleMajor = 10;
    scaleMinor = 10;
    startAngle = 60;
    endAngle = 60;

    animation = false;
    animationStep = 0.5;

    crownColorStart = QColor(255, 255, 255);
    crownColorEnd = QColor(166, 166, 166);
    foreground = QColor(255, 255, 255);
    background = QColor(65, 65, 65);
    pointerColor = QColor(160, 160, 160);

    reverse = false;
    currentValue = 0;
    timer = new QTimer(this);
    timer->setInterval(10);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateValue()));

    setFont(QFont("Arial", 7));
}

GaugeWatch::~GaugeWatch()
{
    if (timer->isActive()) {
        timer->stop();
    }
}

void GaugeWatch::paintEvent(QPaintEvent *)
{
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    //绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.translate(width / 2, height / 2);    
    painter.scale(side / 200.0, side / 200.0);

    //绘制外边框
    drawCrown(&painter);
    //绘制背景
    drawBg(&painter);
    //绘制刻度线
    drawScale(&painter);
    //绘制刻度值
    drawScaleNum(&painter);
    //绘制标题
    drawTitle(&painter);
    //绘制当前值
    drawValue(&painter);
    //绘制指针
    drawIndicator(&painter);
}

void GaugeWatch::drawCrown(QPainter *painter)
{
    int radius = 99;
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient crownGradient(0, -radius, 0, radius);
    crownGradient.setColorAt(0, crownColorStart);
    crownGradient.setColorAt(1, crownColorEnd);
    painter->setBrush(crownGradient);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void GaugeWatch::drawBg(QPainter *painter)
{
    int radius = 92;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(background);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void GaugeWatch::drawScale(QPainter *painter)
{
    int radius = 72;
    painter->save();
    painter->setPen(foreground);

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

void GaugeWatch::drawScaleNum(QPainter *painter)
{
    int radius = 82;
    painter->save();
    painter->setPen(foreground);

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

void GaugeWatch::drawTitle(QPainter *painter)
{
    painter->save();
    painter->setPen(foreground);
    painter->setFont(QFont("Microsoft Yahei", 10));
    double textWidth = painter->fontMetrics().width(title);
    painter->drawText(-textWidth / 2, -30, title);
    painter->restore();
}

void GaugeWatch::drawValue(QPainter *painter)
{
    painter->save();
    painter->setPen(foreground);
    painter->setFont(QFont("Arial", 9));
    QString strValue = QString("%1 %2").arg(currentValue, 0, 'f', precision).arg(unit);
    double textWidth = painter->fontMetrics().width(strValue);
    painter->drawText(-textWidth / 2, 42, strValue);
    painter->restore();
}

void GaugeWatch::drawIndicator(QPainter *painter)
{
    painter->save();
    QPolygon pts;
    pts.setPoints(3, -2, 0, 2, 0, 0, 60);

    painter->rotate(startAngle);
    double degRotate = (360.0 - startAngle - endAngle) / (maxValue - minValue) * (currentValue - minValue);

    //画指针
    painter->rotate(degRotate);
    QRadialGradient haloGradient(0, 0, 60, 0, 0);
    haloGradient.setColorAt(0, pointerColor.lighter(100));
    haloGradient.setColorAt(1, pointerColor);
    painter->setPen(foreground);
    painter->setBrush(haloGradient);
    painter->drawConvexPolygon(pts);
    painter->restore();

    //画中心点
    painter->save();
    QConicalGradient coneGradient(0, 0, -90.0);
    coneGradient.setColorAt(0.0, background);
    coneGradient.setColorAt(0.5, foreground);
    coneGradient.setColorAt(1.0, background);
    painter->setPen(Qt::NoPen);
    painter->setBrush(coneGradient);
    painter->drawEllipse(-5, -5, 10, 10);
    painter->restore();
}

void GaugeWatch::updateValue()
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

double GaugeWatch::getMinValue() const
{
    return this->minValue;
}

double GaugeWatch::getMaxValue() const
{
    return this->maxValue;
}

double GaugeWatch::getValue() const
{
    return this->value;
}

int GaugeWatch::getPrecision() const
{
    return this->precision;
}

QString GaugeWatch::getUnit() const
{
    return this->unit;
}

QString GaugeWatch::getTitle() const
{
    return this->title;
}

int GaugeWatch::getScaleMajor() const
{
    return this->scaleMajor;
}

int GaugeWatch::getScaleMinor() const
{
    return this->scaleMinor;
}

int GaugeWatch::getStartAngle() const
{
    return this->startAngle;
}

int GaugeWatch::getEndAngle() const
{
    return this->endAngle;
}

bool GaugeWatch::getAnimation() const
{
    return this->animation;
}

double GaugeWatch::getAnimationStep() const
{
    return this->animationStep;
}

QColor GaugeWatch::getCrownColorStart() const
{
    return this->crownColorStart;
}

QColor GaugeWatch::getCrownColorEnd() const
{
    return this->crownColorEnd;
}

QColor GaugeWatch::getForeground() const
{
    return this->foreground;
}

QColor GaugeWatch::getBackground() const
{
    return this->background;
}

QColor GaugeWatch::getPointerColor() const
{
    return this->pointerColor;
}

QSize GaugeWatch::sizeHint() const
{
    return QSize(200, 200);
}

QSize GaugeWatch::minimumSizeHint() const
{
    return QSize(50, 50);
}

void GaugeWatch::setRange(double minValue, double maxValue)
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

void GaugeWatch::setRange(int minValue, int maxValue)
{
    setRange((double)minValue, (double)maxValue);
}

void GaugeWatch::setMinValue(double minValue)
{
    setRange(minValue, maxValue);
}

void GaugeWatch::setMaxValue(double maxValue)
{
    setRange(minValue, maxValue);
}

void GaugeWatch::setValue(double value)
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

void GaugeWatch::setValue(int value)
{
    setValue((double)value);
}

void GaugeWatch::setPrecision(int precision)
{
    //最大精确度为 3
    if (precision <= 3 && this->precision != precision) {
        this->precision = precision;
        update();
    }
}

void GaugeWatch::setUnit(const QString &unit)
{
    if (this->unit != unit) {
        this->unit = unit;
        update();
    }
}

void GaugeWatch::setTitle(const QString &title)
{
    if (this->title != title) {
        this->title = title;
        update();
    }
}

void GaugeWatch::setScaleMajor(int scaleMajor)
{
    if (this->scaleMajor != scaleMajor) {
        this->scaleMajor = scaleMajor;
        update();
    }
}

void GaugeWatch::setScaleMinor(int scaleMinor)
{
    if (this->scaleMinor != scaleMinor) {
        this->scaleMinor = scaleMinor;
        update();
    }
}

void GaugeWatch::setStartAngle(int startAngle)
{
    if (this->startAngle != startAngle) {
        this->startAngle = startAngle;
        update();
    }
}

void GaugeWatch::setEndAngle(int endAngle)
{
    if (this->endAngle != endAngle) {
        this->endAngle = endAngle;
        update();
    }
}

void GaugeWatch::setAnimation(bool animation)
{
    if (this->animation != animation) {
        this->animation = animation;
        update();
    }
}

void GaugeWatch::setAnimationStep(double animationStep)
{
    if (this->animationStep != animationStep) {
        this->animationStep = animationStep;
        update();
    }
}

void GaugeWatch::setCrownColorStart(const QColor &crownColorStart)
{
    if (this->crownColorStart != crownColorStart) {
        this->crownColorStart = crownColorStart;
        update();
    }
}

void GaugeWatch::setCrownColorEnd(const QColor &crownColorEnd)
{
    if (this->crownColorEnd != crownColorEnd) {
        this->crownColorEnd = crownColorEnd;
        update();
    }
}

void GaugeWatch::setForeground(const QColor &foreground)
{
    if (this->foreground != foreground) {
        this->foreground = foreground;
        update();
    }
}

void GaugeWatch::setBackground(const QColor &background)
{
    if (this->background != background) {
        this->background = background;
        update();
    }
}

void GaugeWatch::setPointerColor(const QColor &pointerColor)
{
    if (this->pointerColor != pointerColor) {
        this->pointerColor = pointerColor;
        update();
    }
}
