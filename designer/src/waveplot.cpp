#include "waveplot.h"
#include "qpainter.h"
#include "qmath.h"
#include "qdebug.h"

WavePlot::WavePlot(QWidget *parent) : QWidget(parent)
{
    flag1 = 20;
    flag2 = 100;
    init();
}

void WavePlot::resizeEvent(QResizeEvent *)
{
    init();
}

void WavePlot::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setBrush(QColor(100, 100, 100));
    painter.drawRect(0, 0, this->width(), this->height());

    QPoint beginPoint;
    QPoint endPoint;
    painter.setPen(QColor(255, 255, 255));

    int offset = this->height() / 2;

    for( int i = 0; i < pointCount - 1; i++ ) {
        beginPoint.setX(i);
        beginPoint.setY(buffer.at(i) + offset);
        endPoint.setX(i + 1);
        endPoint.setY(buffer.at(i + 1) + offset);
        painter.drawLine(beginPoint, endPoint);
    }
}

QSize WavePlot::sizeHint() const
{
    return QSize(200, 100);
}

QSize WavePlot::minimumSizeHint() const
{
    return QSize(20, 10);
}

void WavePlot::init()
{
    pointCount = this->width();
    buffer.clear();
    for( int i = 0; i < pointCount; i++ ) {
        buffer.append((int)(qSin((i * M_PI) / flag2) * flag1));
    }
}

void WavePlot::clear()
{
    int tmp = buffer.at(0);
    int i;
    for(i = 0; i < pointCount - 1; i++) {
        buffer[i] = buffer.at(i + 1);
    }
    buffer[pointCount - 1] = tmp;

    update();
}

void WavePlot::changeFlag1(int flag1)
{
    this->flag1 = flag1;
    this->init();
}

void WavePlot::changeFlag2(int flag2)
{
    this->flag2 = flag2;
    this->init();
}
