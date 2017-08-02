#pragma execution_character_set("utf-8")

#include "waveline.h"
#include "qpainter.h"
#include "qtimer.h"
#include "qdebug.h"

WaveLine::WaveLine(QWidget *parent) : QWidget(parent)
{
    maxValue = 100;
    step = 1;
    space = 10;

    bgColorStart = QColor(100, 100, 100);
    bgColorEnd = QColor(60, 60, 60);
    lineColor = QColor(100, 184, 255);

    timer = new QTimer(this);
    timer->setInterval(10);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateData()));
}

WaveLine::~WaveLine()
{
    if (timer->isActive()) {
        timer->stop();
    }
}

void WaveLine::paintEvent(QPaintEvent *)
{
    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //绘制背景
    drawBg(&painter);
    //绘制线条
    drawLine(&painter);
}

void WaveLine::drawBg(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient bgGradient(QPoint(0, 0), QPoint(0, height()));
    bgGradient.setColorAt(0.0, bgColorStart);
    bgGradient.setColorAt(1.0, bgColorEnd);
    painter->setBrush(bgGradient);
    painter->drawRect(rect());
    painter->restore();
}

void WaveLine::drawLine(QPainter *painter)
{
    painter->save();
    painter->setPen(QPen(lineColor, 2));

    int count = dataVec.count();
    double increment = (double)width() / count;
    double initX = 0;
    QVector<QPointF> pointVec;

    for (int i = 0; i < count - 1; i++) {
        double currentValue = currentDataVec.at(i);
        double y1 = height() - (double)height() / maxValue * currentValue;
        double nextValue = currentDataVec.at(i + 1);
        double y2 = height() - (double)height() / maxValue * nextValue;

        QPointF point1(initX, y1);
        QPointF point2(initX + increment, y2);
        initX += increment;

        pointVec.append(point1);
        pointVec.append(point2);
    }

    painter->drawLines(pointVec);
    painter->restore();
}

void WaveLine::updateData()
{
    int count = dataVec.count();

    for (int i = 0; i < count; i++) {
        if (currentDataVec.at(i) < dataVec.at(i)) {
            currentDataVec[i] += step;
        } else if (currentDataVec.at(i) > dataVec.at(i)) {
            currentDataVec[i] -= step;
        } else {
            continue;
        }
    }

    update();
}

int WaveLine::getMaxValue() const
{
    return this->maxValue;
}

int WaveLine::getStep() const
{
    return this->step;
}

int WaveLine::getSpace() const
{
    return this->space;
}

QColor WaveLine::getBgColorStart() const
{
    return this->bgColorStart;
}

QColor WaveLine::getBgColorEnd() const
{
    return this->bgColorEnd;
}

QColor WaveLine::getLineColor() const
{
    return this->lineColor;
}

QSize WaveLine::sizeHint() const
{
    return QSize(50, 200);
}

QSize WaveLine::minimumSizeHint() const
{
    return QSize(10, 20);
}

void WaveLine::setData(const QVector<int> &dataVec)
{
    int count = dataVec.count();
    this->currentDataVec.resize(count);
    this->dataVec.resize(count);

    for (int i = 0; i < count; i++) {
        this->dataVec[i] = dataVec.at(i);
    }

    if (!timer->isActive()) {
        timer->start();
    }
}

void WaveLine::setMaxValue(int maxValue)
{
    if (this->maxValue != maxValue) {
        this->maxValue = maxValue;
        update();
    }
}

void WaveLine::setStep(int step)
{
    if (this->step != step) {
        this->step = step;
        update();
    }
}

void WaveLine::setSpace(int space)
{
    if (this->space != space) {
        this->space = space;
        update();
    }
}

void WaveLine::setBgColorStart(const QColor &bgColorStart)
{
    if (this->bgColorStart != bgColorStart) {
        this->bgColorStart = bgColorStart;
        update();
    }
}

void WaveLine::setBgColorEnd(const QColor &bgColorEnd)
{
    if (this->bgColorEnd != bgColorEnd) {
        this->bgColorEnd = bgColorEnd;
        update();
    }
}

void WaveLine::setLineColor(const QColor &lineColor)
{
    if (this->lineColor != lineColor) {
        this->lineColor = lineColor;
        update();
    }
}
