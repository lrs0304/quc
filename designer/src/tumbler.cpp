#pragma execution_character_set("utf-8")

#include "tumbler.h"
#include "qpainter.h"
#include "qevent.h"
#include "qdebug.h"

Tumbler::Tumbler(QWidget *parent) : QWidget(parent)
{
    currentIndex = 0;
    currentValue = "1";

    for (int i = 1; i <= 12; i++) {
        listValue.append(QString::number(i));
    }

    foreground = QColor(140, 140, 140);
    background = QColor(40, 40, 40);
    lineColor = QColor(46, 142, 180, 200);
    textColor = QColor(255, 255, 255);

    horizontal = false;

    percent = 3;
    offset = 0;
    pressed = 0;
    pressedPos = 0;
    currentPos = 0;

    setFont(QFont("Arial", 8));
}

void Tumbler::wheelEvent(QWheelEvent *e)
{
    //滚动的角度,*8就是鼠标滚动的距离
    int degrees = e->delta() / 8;

    //滚动的步数,*15就是鼠标滚动的角度
    int steps = degrees / 15;

    //如果是正数代表为左边移动,负数代表为右边移动
    if (e->orientation() == Qt::Vertical) {
        int index = currentIndex - steps;

        if (steps > 0) {
            if (index > 0) {
                setCurrentIndex(index);
            } else {
                setCurrentIndex(0);
            }
        } else {
            if (index < listValue.count() - 1) {
                setCurrentIndex(index);
            } else {
                setCurrentIndex(listValue.count() - 1);
            }
        }
    }
}

void Tumbler::mousePressEvent(QMouseEvent *e)
{
    pressed = true;
    int target = e->pos().x();

    if (!horizontal) {
        target = e->pos().y();
    }

    pressedPos = target;
}

void Tumbler::mouseMoveEvent(QMouseEvent *e)
{
    int count = listValue.count();

    if (count <= 1) {
        return;
    }

    int pos = e->pos().x();
    int target = this->width();

    if (!horizontal) {
        pos = e->pos().y();
        target = this->height();
    }

    int index = listValue.indexOf(currentValue);

    if (pressed) {
        //数值到边界时,阻止继续往对应方向移动
        if ((index == 0 && pos >= pressedPos) || (index == count - 1 && pos <= pressedPos)) {
            return;
        }

        offset = pos - pressedPos;

        //若移动速度过快时进行限制
        if (offset > target / percent) {
            offset = target / percent;
        } else if (offset < -target / percent) {
            offset = -target / percent;
        }

        static int oldIndex = -1;

        if (oldIndex != index) {
            emit currentIndexChanged(index);
            emit currentValueChanged(listValue.at(index));
            oldIndex = index;
        }

        update();
    }
}

void Tumbler::mouseReleaseEvent(QMouseEvent *)
{
    if (pressed) {
        pressed = false;
        //矫正到居中位置
        checkPosition();
    }
}

void Tumbler::paintEvent(QPaintEvent *)
{
    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    int count = listValue.count();

    if (count <= 1) {
        return;
    }

    int target = this->width();

    if (!horizontal) {
        target = this->height();
    }

    int index = listValue.indexOf(currentValue);

    //当右移偏移量大于比例且当前值不是第一个则索引-1
    if (offset >= target / percent && index > 0) {
        pressedPos += target / percent;
        offset -= target / percent;
        index -= 1;
    }

    //当左移偏移量小于比例且当前值不是末一个则索引+1
    if (offset <= -target / percent && index < count - 1) {
        pressedPos -= target / percent;
        offset += target / percent;
        index += 1;
    }

    currentIndex = index;
    currentValue = listValue.at(index);

    //绘制背景
    drawBg(&painter);

    //绘制线条
    drawLine(&painter);

    //绘制中间值
    painter.setPen(textColor);
    drawText(&painter, index, offset);
    painter.setPen(foreground);

    //绘制左侧值
    if (index != 0) {
        drawText(&painter, index - 1, offset - target / percent);
    }

    //绘制右侧值
    if (index != count - 1) {
        drawText(&painter, index + 1, offset + target / percent);
    }
}

void Tumbler::drawBg(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(background);
    painter->drawRect(rect());
    painter->restore();
}

void Tumbler::drawLine(QPainter *painter)
{
    //上下部分偏移量
    int offset = 10;
    int width = this->width();
    int height = this->height();

    painter->save();
    painter->setBrush(Qt::NoBrush);

    QPen pen = painter->pen();
    pen.setWidth(3);
    pen.setColor(lineColor);
    pen.setCapStyle(Qt::RoundCap);
    painter->setPen(pen);

    //每次同时存在三个元素
    if (horizontal) {
        painter->drawLine(width / 3 * 1, offset, width / 3 * 1, height - offset);
        painter->drawLine(width / 3 * 2, offset, width / 3 * 2, height - offset);
    } else {
        painter->drawLine(offset, height / 3 * 1, width - offset,  height / 3 * 1);
        painter->drawLine(offset, height / 3 * 2, width - offset,  height / 3 * 2);
    }

    painter->restore();
}

void Tumbler::drawText(QPainter *painter, int index, int offset)
{
    painter->save();

    int width = this->width();
    int height = this->height();
    QString strValue = listValue.at(index);

    int target = width;

    if (!horizontal) {
        target = height;
    }

    QFont font = painter->font();
    font.setPixelSize((target - qAbs(offset)) / 8);
    painter->setFont(font);

    if (horizontal) {
        int textWidth = painter->fontMetrics().width(strValue);
        int initX = width / 2 + offset - textWidth / 2;
        painter->drawText(QRect(initX, 0, textWidth, height), Qt::AlignCenter, strValue);

        //计算最后中间值停留的起始坐标,以便鼠标松开时矫正居中
        if (index == currentIndex) {
            currentPos = initX;
        }
    } else {
        int textHeight = painter->fontMetrics().height();
        int initY = height / 2 + offset - textHeight / 2;
        painter->drawText(QRect(0, initY, width, textHeight), Qt::AlignCenter, strValue);

        //计算最后中间值停留的起始坐标,以便鼠标松开时矫正居中
        if (index == currentIndex) {
            currentPos = initY;
        }
    }

    painter->restore();
}

void Tumbler::checkPosition()
{
    int target = this->width();

    if (!horizontal) {
        target = this->height();
    }

    //左右滑动样式,往左滑动时,offset为负数,当前值所在X轴坐标小于宽度的一半,则将当前值设置为下一个值
    //左右滑动样式,往右滑动时,offset为正数,当前值所在X轴坐标大于宽度的一半,则将当前值设置为上一个值
    //上下滑动样式,往上滑动时,offset为负数,当前值所在Y轴坐标小于高度的一半,则将当前值设置为下一个值
    //上下滑动样式,往下滑动时,offset为正数,当前值所在Y轴坐标大于高度的一半,则将当前值设置为上一个值
    if (offset < 0) {
        if (currentPos < target / 2) {
            offset = 0;
            setCurrentIndex(currentIndex + 1);
        }
    } else {
        if (currentPos > target / 2) {
            offset = 0;
            setCurrentIndex(currentIndex - 1);
        }
    }
}

QStringList Tumbler::getListValue() const
{
    return this->listValue;
}

int Tumbler::getCurrentIndex() const
{
    return this->currentIndex;
}

QString Tumbler::getCurrentValue() const
{
    return this->currentValue;
}

bool Tumbler::getHorizontal() const
{
    return this->horizontal;
}

QColor Tumbler::getForeground() const
{
    return this->foreground;
}

QColor Tumbler::getBackground() const
{
    return this->background;
}

QColor Tumbler::getLineColor() const
{
    return this->lineColor;
}

QColor Tumbler::getTextColor() const
{
    return this->textColor;
}

QSize Tumbler::sizeHint() const
{
    return QSize(50, 150);
}

QSize Tumbler::minimumSizeHint() const
{
    return QSize(10, 10);
}

void Tumbler::setListValue(const QStringList &listValue)
{
    if (listValue.count() > 0) {
        this->listValue = listValue;
        setCurrentIndex(0);
        setCurrentValue(listValue.at(0));
        update();
    }
}

void Tumbler::setCurrentIndex(int currentIndex)
{
    if (currentIndex >= 0) {
        this->currentIndex = currentIndex;
        this->currentValue = listValue.at(currentIndex);
        emit currentIndexChanged(currentIndex);
        update();
    }
}

void Tumbler::setCurrentValue(const QString &currentValue)
{
    if (listValue.contains(currentValue)) {
        this->currentValue = currentValue;
        this->currentIndex = listValue.indexOf(currentValue);
        emit currentValueChanged(currentValue);
        update();
    }
}

void Tumbler::setHorizontal(bool horizontal)
{
    if (this->horizontal != horizontal){
        this->horizontal = horizontal;
        update();
    }
}

void Tumbler::setForeground(const QColor &foreground)
{
    if (this->foreground != foreground){
        this->foreground = foreground;
        update();
    }
}

void Tumbler::setBackground(const QColor &background)
{
    if (this->background != background){
        this->background = background;
        update();
    }
}

void Tumbler::setLineColor(const QColor &lineColor)
{
    if (this->lineColor != lineColor){
        this->lineColor = lineColor;
        update();
    }
}

void Tumbler::setTextColor(const QColor &textColor)
{
    if (this->textColor != textColor){
        this->textColor = textColor;
        update();
    }
}
