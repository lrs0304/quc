#pragma execution_character_set("utf-8")

#include "animationbutton1.h"
#include "qpainter.h"
#include "qpropertyanimation.h"
#include "qdebug.h"

AnimationButton1::AnimationButton1(QWidget *parent) : QWidget(parent)
{
    enter = true;
    leave = false;
    pixWidth = 0;
    pixHeight = 0;
    oldWidth = 0;
    oldHeight = 0;

    enterAnimation = new QPropertyAnimation(this, "");
    enterAnimation->setStartValue(0);
    enterAnimation->setEndValue(5);
    enterAnimation->setDuration(200);
    connect(enterAnimation, SIGNAL(valueChanged(QVariant)), this, SLOT(enterImageChanged(QVariant)));

    leaveAnimation = new QPropertyAnimation(this, "");
    leaveAnimation->setStartValue(0);
    leaveAnimation->setEndValue(5);
    leaveAnimation->setDuration(200);
    connect(leaveAnimation, SIGNAL(valueChanged(QVariant)), this, SLOT(leaveImageChanged(QVariant)));
}

AnimationButton1::~AnimationButton1()
{
    delete enterAnimation;
    delete leaveAnimation;
}

void AnimationButton1::enterEvent(QEvent *)
{
    enter = true;
    leave = false;
    pixWidth = pixWidth - 25;
    pixHeight = pixHeight - 25;
    enterAnimation->start();
}

void AnimationButton1::leaveEvent(QEvent *)
{
    enter = false;
    leave = true;
    pixWidth = oldWidth;
    pixHeight = oldHeight;
    leaveAnimation->start();
}

void AnimationButton1::paintEvent(QPaintEvent *)
{
    if (imageName.isEmpty()) {
        return;
    }

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    QPixmap pix(imageName);
    pix = pix.scaled(targetWidth, targetHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    if (enter || leave) {
        int pixX = rect().center().x() - targetWidth / 2;
        int pixY = rect().center().y() - targetHeight / 2;
        QPoint point(pixX, pixY);
        painter.drawPixmap(point, pix);
    }
}

void AnimationButton1::enterImageChanged(QVariant index)
{
    int i = index.toInt();
    targetWidth = pixWidth + i * 5;
    targetHeight = pixHeight + i * 5;
    update();
}

void AnimationButton1::leaveImageChanged(QVariant index)
{
    int i = index.toInt();
    targetWidth = pixWidth - i * 5;
    targetHeight = pixWidth - i * 5;
    update();
}

QString AnimationButton1::getImageName() const
{
    return this->imageName;
}

QSize AnimationButton1::sizeHint() const
{
    return QSize(95, 95);
}

QSize AnimationButton1::minimumSizeHint() const
{
    return QSize(10, 10);
}

void AnimationButton1::setImageName(const QString &imageName)
{
    if (this->imageName != imageName) {
        this->imageName = imageName;
        QPixmap pix(imageName);
        pixWidth = pix.width();
        pixHeight = pix.height();
        oldWidth = pixWidth;
        oldHeight = pixHeight;
        targetWidth = pixWidth - 25;
        targetHeight = pixHeight - 25;
        update();
    }
}
