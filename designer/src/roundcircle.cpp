#pragma execution_character_set("utf-8")

#include "roundcircle.h"
#include "qpainter.h"
#include "qtimer.h"
#include "qdebug.h"

RoundCircle::RoundCircle(QWidget *parent) :	QWidget(parent)
{
    angle = 0;
    radius = 0;

    step = 5;
    clockWise = true;

    bgColorStart = QColor(65, 65, 65);
    bgColorEnd = QColor(89, 89, 89);

    pieColor1Start = QColor(0, 133, 203);
    pieColor1End = QColor(0, 118, 177);
    pieColor2Start = QColor(255, 255, 255);
    pieColor2End = QColor(233, 233, 233);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateAngle()));
    timer->start(30);
}

RoundCircle::~RoundCircle()
{
    if (timer->isActive()) {
        timer->stop();
    }
}

void RoundCircle::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    radius = qMin(width(), height()) / 2 - 5;
    drawBg(&painter);
    drawPie(&painter);
}

void RoundCircle::drawBg(QPainter *painter)
{
    painter->save();

    QPointF topLeft(rect().center().x() - radius, rect().center().y() - radius);
    QPointF bottomRight(rect().center().x() + radius, rect().center().y() + radius);
    QRectF bgRect(topLeft, bottomRight);

    painter->setPen(Qt::NoPen);
    QRadialGradient bgGradient(bgRect.center(), radius, bgRect.center());
    bgGradient.setColorAt(0.0, bgColorStart);
    bgGradient.setColorAt(1.0, bgColorEnd);
    painter->setBrush(bgGradient);
    painter->drawEllipse(bgRect);

    painter->restore();
}

void RoundCircle::drawPie(QPainter *painter)
{
    painter->save();

    QTransform t;
    t.translate(rect().center().x(), rect().center().y());

    if (clockWise) {
        t.rotate(angle);
    } else {
        t.rotate(-angle);
    }

    painter->setTransform(t);

    double innerRadius = radius * 0.8;
    QPointF topLeft(-innerRadius, -innerRadius);
    QPointF bottomRight(innerRadius, innerRadius);
    QRectF  pieRect(topLeft, bottomRight);

    double dAngle = 90 * 16;
    double startAngle = 0;

    painter->setPen(Qt::NoPen);

    for (int index = 0; index < 4; index++) {
        QRadialGradient pieGradient(pieRect.center(), radius, pieRect.center());

        if (index % 2) {
            pieGradient.setColorAt(0.0, pieColor1Start);
            pieGradient.setColorAt(1.0, pieColor1End);
        } else {
            pieGradient.setColorAt(0.0, pieColor2Start);
            pieGradient.setColorAt(1.0, pieColor2End);
        }

        painter->setBrush(pieGradient);
        painter->drawPie(pieRect, startAngle, dAngle);
        startAngle += dAngle;
    }

    painter->restore();
}

void RoundCircle::updateAngle()
{
    angle += step;

    if (angle > 360) {
        angle = 0;
    }

    update();
}

int RoundCircle::getStep() const
{
    return this->step;
}

bool RoundCircle::getClockWise() const
{
    return this->clockWise;
}

QColor RoundCircle::getBgColorStart() const
{
    return this->bgColorStart;
}

QColor RoundCircle::getBgColorEnd() const
{
    return this->bgColorEnd;
}

QColor RoundCircle::getPieColor1Start() const
{
    return this->pieColor1Start;
}

QColor RoundCircle::getPieColor1End() const
{
    return this->pieColor1End;
}

QColor RoundCircle::getPieColor2Start() const
{
    return this->pieColor2Start;
}

QColor RoundCircle::getPieColor2End() const
{
    return this->pieColor2End;
}

QSize RoundCircle::sizeHint() const
{
    return QSize(100, 100);
}

QSize RoundCircle::minimumSizeHint() const
{
    return QSize(10, 10);
}

void RoundCircle::setStep(int step)
{
    if (this->step != step) {
        this->step = step;
        update();
    }
}

void RoundCircle::setClockWise(bool clockWise)
{
    if (this->clockWise != clockWise) {
        this->clockWise = clockWise;
        update();
    }
}

void RoundCircle::setBgColorStart(const QColor &bgColorStart)
{
    if (this->bgColorStart != bgColorStart) {
        this->bgColorStart = bgColorStart;
        update();
    }
}

void RoundCircle::setBgColorEnd(const QColor &bgColorEnd)
{
    if (this->bgColorEnd != bgColorEnd) {
        this->bgColorEnd = bgColorEnd;
        update();
    }
}

void RoundCircle::setPieColor1Start(const QColor &pieColor1Start)
{
    if (this->pieColor1Start != pieColor1Start) {
        this->pieColor1Start = pieColor1Start;
        update();
    }
}

void RoundCircle::setPieColor1End(const QColor &pieColor1End)
{
    if (this->pieColor1End != pieColor1End) {
        this->pieColor1End = pieColor1End;
        update();
    }
}

void RoundCircle::setPieColor2Start(const QColor &pieColor2Start)
{
    if (this->pieColor2Start != pieColor2Start) {
        this->pieColor2Start = pieColor2Start;
        update();
    }
}

void RoundCircle::setPieColor2End(const QColor &pieColor2End)
{
    if (this->pieColor2End != pieColor2End) {
        this->pieColor2End = pieColor2End;
        update();
    }
}
