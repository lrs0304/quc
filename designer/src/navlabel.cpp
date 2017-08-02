#pragma execution_character_set("utf-8")

#include "navlabel.h"
#include "qpainter.h"
#include "qdebug.h"

NavLabel::NavLabel(QWidget *parent) : QLabel(parent)
{
    arrowStyle = ArrowStyle_Right;
    background = QColor(100, 184, 255);
    foreground = QColor(255, 255, 255);

    rect = this->geometry();

    setFont(QFont("Microsoft Yahei", 10));
}

void NavLabel::paintEvent(QPaintEvent *)
{
    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //绘制背景
    drawBg(&painter);
    //绘制文字
    drawText(&painter);
}

void NavLabel::drawBg(QPainter *painter)
{
    QPolygon pts;

    int width = this->width();
    int height = this->height();

    int radius = height / 5;
    int radiusX = radius;
    int radiusY = radius + 10;
    int len = width / 20;

    if (arrowStyle == ArrowStyle_Top || arrowStyle == ArrowStyle_Bottom) {
        radius = width / 5;
        radiusX = radius + 10;
        radiusY = radius;
        len = height / 20;
    }

    int endX = width - len;
    int endY = height - len;

    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(background);

    if (arrowStyle == ArrowStyle_Right) {
        rect = QRect(0, 0, endX, height);
        pts.setPoints(3, endX, height / 3 * 1, endX, height / 3 * 2, width, height / 2);
    } else if (arrowStyle == ArrowStyle_Left) {
        rect = QRect(len, 0, width, height);
        pts.setPoints(3, len, height / 3 * 1, len, height / 3 * 2, 0, height / 2);
    } else if (arrowStyle == ArrowStyle_Bottom) {
        rect = QRect(0, 0, width, endY);
        pts.setPoints(3, width / 3 * 1, endY, width / 3 * 2, endY, width / 2, height);
    } else if (arrowStyle == ArrowStyle_Top) {
        rect = QRect(0, len, width, height);
        pts.setPoints(3, width / 3 * 1, len, width / 3 * 2, len, width / 2, 0);
    }

    //绘制圆角矩形
    painter->drawRoundRect(rect, radiusX, radiusY);
    //绘制三角箭头
    painter->drawPolygon(pts);

    painter->restore();
}

void NavLabel::drawText(QPainter *painter)
{
    painter->save();
    painter->setPen(foreground);
    painter->setBrush(Qt::NoBrush);
    painter->drawText(rect, Qt::AlignCenter, this->text());
    painter->restore();
}

NavLabel::ArrowStyle NavLabel::getArrowStyle() const
{
    return this->arrowStyle;
}

QColor NavLabel::getBackground() const
{
    return this->background;
}

QColor NavLabel::getForeground() const
{
    return this->foreground;
}

QSize NavLabel::sizeHint() const
{
    return QSize(100, 30);
}

QSize NavLabel::minimumSizeHint() const
{
    return QSize(20, 10);
}

void NavLabel::setArrowStyle(NavLabel::ArrowStyle arrowStyle)
{
    if (this->arrowStyle != arrowStyle){
        this->arrowStyle = arrowStyle;
        update();
    }
}

void NavLabel::setBackground(const QColor &background)
{
    if (this->background != background){
        this->background = background;
        update();
    }
}

void NavLabel::setForeground(const QColor &foreground)
{
    if (this->foreground != foreground){
        this->foreground = foreground;
        update();
    }
}
