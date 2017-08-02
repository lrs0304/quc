#pragma execution_character_set("utf-8")

#include "lcdnumber.h"
#include "qpainter.h"
#include "qtimer.h"
#include "qdebug.h"

LcdNumber::LcdNumber(QWidget *parent) :	QWidget(parent)
{
    number = 0;
    space = 20;

    bgColorStart = QColor(100, 100, 100);
    bgColorEnd = QColor(60, 60, 60);

    numberColorStart = QColor(100, 184, 255);
    numberColorEnd = QColor(79, 148, 205);
}

void LcdNumber::paintEvent(QPaintEvent *)
{
    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //绘制背景
    drawBg(&painter);
    //绘制数字
    drawNumber(&painter);
}

void LcdNumber::drawBg(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient bgGradient(QPointF(0, 0), QPointF(0, height()));
    bgGradient.setColorAt(0.0, bgColorStart);
    bgGradient.setColorAt(1.0, bgColorEnd);
    painter->setBrush(bgGradient);
    painter->drawRect(rect());
    painter->restore();
}

void LcdNumber::drawNumber(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);

    //找出六个对应点
    QPointF topLeft(space, space);
    QPointF topRight(width() - space, space);
    QPointF midLeft(space, height() / 2);
    QPointF midRight(width() - space, height() / 2);
    QPointF bottomLeft(space, height() - space);
    QPointF bottomRight(width() - space, height() - space);

    //形状宽度及凸起部分高度
    double recWidth = width() / 10;
    double recHeight = height() / 30;
    double recSpace = width() / 30;

    //逐个将每个形状的点集合添加,每个数码管都有7个形状,每个形状有4-6个点

    //左侧上部分形状坐标集合
    QVector<QPointF> topLeftRectVec;
    topLeftRectVec.append(QPointF(topLeft.x(), topLeft.y()));
    topLeftRectVec.append(QPointF(topLeft.x() + recWidth, topLeft.y() + recHeight * 2));
    topLeftRectVec.append(QPointF(midLeft.x() + recWidth, midLeft.y() - recHeight - recSpace));
    topLeftRectVec.append(QPointF(midLeft.x() + recWidth / 2, midLeft.y() - recSpace));
    topLeftRectVec.append(QPointF(midLeft.x(), midLeft.y() - recHeight - recSpace));

    //顶部形状坐标集合
    QVector<QPointF> topRectVec;
    topRectVec.append(QPointF(topLeft.x() + recSpace, topLeft.y()));
    topRectVec.append(QPointF(topLeft.x() + recWidth + recSpace, topLeft.y() + recHeight * 2));
    topRectVec.append(QPointF(topRight.x() - recWidth - recSpace, topRight.y() + recHeight * 2));
    topRectVec.append(QPointF(topRight.x() - recSpace, topRight.y()));

    //右侧上部分形状坐标集合
    QVector<QPointF> topRightRectVec;
    topRightRectVec.append(QPointF(topRight.x() - recWidth, topRight.y() + recHeight * 2));
    topRightRectVec.append(QPointF(topRight.x(), topRight.y()));
    topRightRectVec.append(QPointF(midRight.x(), midRight.y() - recHeight - recSpace));
    topRightRectVec.append(QPointF(midRight.x() - recWidth / 2, midRight.y() - recSpace));
    topRightRectVec.append(QPointF(midRight.x() - recWidth, midRight.y() - recHeight - recSpace));

    //中间部分形状坐标集合
    QVector<QPointF> midRectVec;
    midRectVec.append(QPointF(midLeft.x() + recWidth / 2, midLeft.y()));
    midRectVec.append(QPointF(midLeft.x() + recWidth, midLeft.y() - recHeight));
    midRectVec.append(QPointF(midRight.x() - recWidth, midRight.y() - recHeight));
    midRectVec.append(QPointF(midRight.x() - recWidth / 2, midRight.y()));
    midRectVec.append(QPointF(midRight.x() - recWidth, midRight.y() + recHeight));
    midRectVec.append(QPointF(midLeft.x() + recWidth, midRight.y() + recHeight));

    //左侧下部分形状坐标集合
    QVector<QPointF> bottomLeftRectVec;
    bottomLeftRectVec.append(QPointF(midLeft.x(), midLeft.y() + recHeight + recSpace));
    bottomLeftRectVec.append(QPointF(midLeft.x() + recWidth / 2, midLeft.y() + recSpace));
    bottomLeftRectVec.append(QPointF(midLeft.x() + recWidth, midLeft.y() + recHeight + recSpace));
    bottomLeftRectVec.append(QPointF(bottomLeft.x() + recWidth, bottomLeft.y() - recHeight * 2));
    bottomLeftRectVec.append(QPointF(bottomLeft.x(), bottomLeft.y()));

    //底部形状坐标集合
    QVector<QPointF> bottomRectVec;
    bottomRectVec.append(QPointF(bottomLeft.x() + recSpace, bottomLeft.y()));
    bottomRectVec.append(QPointF(bottomLeft.x() + recWidth + recSpace, bottomRight.y() - recHeight * 2));
    bottomRectVec.append(QPointF(bottomRight.x() - recWidth - recSpace, bottomRight.y() - recHeight * 2));
    bottomRectVec.append(QPointF(bottomRight.x() - recSpace, bottomRight.y()));

    //右侧下部分形状坐标集合
    QVector<QPointF> bottomRightRectVec;
    bottomRightRectVec.append(QPointF(midRight.x() - recWidth, midRight.y() + recHeight + recSpace));
    bottomRightRectVec.append(QPointF(midRight.x() - recWidth / 2, midRight.y() + recSpace));
    bottomRightRectVec.append(QPointF(midRight.x(), midRight.y() + recHeight + recSpace));
    bottomRightRectVec.append(QPointF(bottomRight.x(), bottomRight.y()));
    bottomRightRectVec.append(QPointF(bottomRight.x() - recWidth, bottomRight.y() - recHeight * 2));

    //颜色渐变
    QLinearGradient numberGradient(QPointF(0, 0), QPointF(0, height()));
    numberGradient.setColorAt(0.0, numberColorStart);
    numberGradient.setColorAt(1.0, numberColorEnd);
    painter->setBrush(numberGradient);

    //根据值绘制形状
    switch (number) {
    case 0:
        painter->drawPolygon(topLeftRectVec);
        painter->drawPolygon(topRectVec);
        painter->drawPolygon(topRightRectVec);
        //painter->drawPolygon(midRectVec);
        painter->drawPolygon(bottomLeftRectVec);
        painter->drawPolygon(bottomRectVec);
        painter->drawPolygon(bottomRightRectVec);
        break;

    case 1:
        //painter->drawPolygon(topLeftRectVec);
        //painter->drawPolygon(topRectVec);
        painter->drawPolygon(topRightRectVec);
        //painter->drawPolygon(midRectVec);
        //painter->drawPolygon(bottomLeftRectVec);
        //painter->drawPolygon(bottomRectVec);
        painter->drawPolygon(bottomRightRectVec);
        break;

    case 2:
        //painter->drawPolygon(topLeftRectVec);
        painter->drawPolygon(topRectVec);
        painter->drawPolygon(topRightRectVec);
        painter->drawPolygon(midRectVec);
        painter->drawPolygon(bottomLeftRectVec);
        painter->drawPolygon(bottomRectVec);
        //painter->drawPolygon(bottomRightRectVec);
        break;

    case 3:
        //painter->drawPolygon(topLeftRectVec);
        painter->drawPolygon(topRectVec);
        painter->drawPolygon(topRightRectVec);
        painter->drawPolygon(midRectVec);
        //painter->drawPolygon(bottomLeftRectVec);
        painter->drawPolygon(bottomRectVec);
        painter->drawPolygon(bottomRightRectVec);
        break;

    case 4:
        painter->drawPolygon(topLeftRectVec);
        //painter->drawPolygon(topRectVec);
        painter->drawPolygon(topRightRectVec);
        painter->drawPolygon(midRectVec);
        //painter->drawPolygon(bottomLeftRectVec);
        //painter->drawPolygon(bottomRectVec);
        painter->drawPolygon(bottomRightRectVec);
        break;

    case 5:
        painter->drawPolygon(topLeftRectVec);
        painter->drawPolygon(topRectVec);
        //painter->drawPolygon(topRightRectVec);
        painter->drawPolygon(midRectVec);
        //painter->drawPolygon(bottomLeftRectVec);
        painter->drawPolygon(bottomRectVec);
        painter->drawPolygon(bottomRightRectVec);
        break;

    case 6:
        painter->drawPolygon(topLeftRectVec);
        painter->drawPolygon(topRectVec);
        //painter->drawPolygon(topRightRectVec);
        painter->drawPolygon(midRectVec);
        painter->drawPolygon(bottomLeftRectVec);
        painter->drawPolygon(bottomRectVec);
        painter->drawPolygon(bottomRightRectVec);
        break;

    case 7:
        //painter->drawPolygon(topLeftRectVec);
        painter->drawPolygon(topRectVec);
        painter->drawPolygon(topRightRectVec);
        //painter->drawPolygon(midRectVec);
        //painter->drawPolygon(bottomLeftRectVec);
        //painter->drawPolygon(bottomRectVec);
        painter->drawPolygon(bottomRightRectVec);
        break;

    case 8:
        painter->drawPolygon(topLeftRectVec);
        painter->drawPolygon(topRectVec);
        painter->drawPolygon(topRightRectVec);
        painter->drawPolygon(midRectVec);
        painter->drawPolygon(bottomLeftRectVec);
        painter->drawPolygon(bottomRectVec);
        painter->drawPolygon(bottomRightRectVec);
        break;

    case 9:
        painter->drawPolygon(topLeftRectVec);
        painter->drawPolygon(topRectVec);
        painter->drawPolygon(topRightRectVec);
        painter->drawPolygon(midRectVec);
        //painter->drawPolygon(bottomLeftRectVec);
        painter->drawPolygon(bottomRectVec);
        painter->drawPolygon(bottomRightRectVec);
        break;

    default:
        break;
    }

    painter->restore();
}

int LcdNumber::getNumber() const
{
    return this->number;
}

int LcdNumber::getSpace() const
{
    return this->space;
}

QColor LcdNumber::getBgColorStart() const
{
    return this->bgColorStart;
}

QColor LcdNumber::getBgColorEnd() const
{
    return this->bgColorEnd;
}

QColor LcdNumber::getNumberColorStart() const
{
    return this->numberColorStart;
}

QColor LcdNumber::getNumberColorEnd() const
{
    return this->numberColorEnd;
}

QSize LcdNumber::sizeHint() const
{
    return QSize(150, 200);
}

QSize LcdNumber::minimumSizeHint() const
{
    return QSize(20, 30);
}

void LcdNumber::setNumber(int number)
{
    if (this->number != number) {
        this->number = number;
        update();
    }
}

void LcdNumber::setSpace(int space)
{
    if (this->space != space) {
        this->space = space;
        update();
    }
}

void LcdNumber::setBgColorStart(const QColor &bgColorStart)
{
    if (this->bgColorStart != bgColorStart) {
        this->bgColorStart = bgColorStart;
        update();
    }
}

void LcdNumber::setBgColorEnd(const QColor &bgColorEnd)
{
    if (this->bgColorEnd != bgColorEnd) {
        this->bgColorEnd = bgColorEnd;
        update();
    }
}

void LcdNumber::setNumberColorStart(const QColor &numberColorStart)
{
    if (this->numberColorStart != numberColorStart) {
        this->numberColorStart = numberColorStart;
        update();
    }
}

void LcdNumber::setNumberColorEnd(const QColor &numberColorEnd)
{
    if (this->numberColorEnd != numberColorEnd) {
        this->numberColorEnd = numberColorEnd;
        update();
    }
}
