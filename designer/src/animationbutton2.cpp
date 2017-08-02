#pragma execution_character_set("utf-8")

#include "animationbutton2.h"
#include "qpainter.h"
#include "qpropertyanimation.h"
#include "qdebug.h"

AnimationButton2::AnimationButton2(QWidget *parent) : QWidget(parent)
{
    enter = true;
    leave = false;
    enterIndex = 0;
    leaveIndex = 0;

    enterAnimation = new QPropertyAnimation(this, "");
    enterAnimation->setStartValue(0);
    enterAnimation->setEndValue(9);
    enterAnimation->setDuration(500);
    connect(enterAnimation, SIGNAL(valueChanged(QVariant)), this, SLOT(enterImageChanged(QVariant)));

    leaveAnimation = new QPropertyAnimation(this, "");
    leaveAnimation->setStartValue(0);
    leaveAnimation->setEndValue(7);
    leaveAnimation->setDuration(500);
    connect(leaveAnimation, SIGNAL(valueChanged(QVariant)), this, SLOT(leaveImageChanged(QVariant)));
}

AnimationButton2::~AnimationButton2()
{
    delete enterAnimation;
    delete leaveAnimation;
}

void AnimationButton2::enterEvent(QEvent *)
{
    enter = true;
    leave = false;
    enterAnimation->start();
}
void AnimationButton2::leaveEvent(QEvent *)
{
    enter = false;
    leave = true;
    leaveAnimation->start();
}
void AnimationButton2::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //绘制鼠标进入时的图片
    if (enter && listPixEnter.count() > 0) {
        QPixmap pix = listPixEnter.at(enterIndex);

        //按照比例自动居中绘制
        int pixWidth = pix.width();
        int pixHeight = pix.height();
        int pixX = rect().center().x() - pixWidth / 2;
        int pixY = rect().center().y() - pixHeight / 2;
        QPoint point(pixX, pixY);
        painter.drawPixmap(point, pix);
    }

    //绘制鼠标离开时的图片
    if (leave && listPixLeave.count() > 0) {
        QPixmap pix = listPixLeave.at(leaveIndex);

        //按照比例自动居中绘制
        int pixWidth = pix.width();
        int pixHeight = pix.height();
        int pixX = rect().center().x() - pixWidth / 2;
        int pixY = rect().center().y() - pixHeight / 2;
        QPoint point(pixX, pixY);
        painter.drawPixmap(point, pix);
    }
}

void AnimationButton2::enterImageChanged(QVariant index)
{
    enterIndex = index.toInt();
    update();
}

void AnimationButton2::leaveImageChanged(QVariant index)
{
    leaveIndex = index.toInt();
    update();
}

QString AnimationButton2::getNormalImage() const
{
    return this->normalImage;
}

QString AnimationButton2::getEnterImage() const
{
    return this->enterImage;
}

QString AnimationButton2::getLeaveImage() const
{
    return this->leaveImage;
}

QSize AnimationButton2::sizeHint() const
{
    return QSize(95, 95);
}

QSize AnimationButton2::minimumSizeHint() const
{
    return QSize(10, 10);
}

void AnimationButton2::setNormalImage(QString normalImage)
{
    if (this->normalImage != normalImage) {
        this->normalImage = normalImage;
        pixNormal = QPixmap(normalImage);
        update();
    }
}

void AnimationButton2::setEnterImage(QString enterImage)
{
    if (this->enterImage != enterImage) {
        this->enterImage = enterImage;
        QPixmap pixEnter(enterImage);
        listPixEnter.clear();

        for (int i = 0; i < 10; i++) {
            listPixEnter << pixEnter.copy(i * (pixEnter.width() / 10), 0, pixEnter.width() / 10, pixEnter.height());
        }

        update();
    }
}

void AnimationButton2::setLeaveImage(QString leaveImage)
{
    if (this->leaveImage != leaveImage) {
        this->leaveImage = leaveImage;
        QPixmap pixLeave(leaveImage);
        listPixLeave.clear();

        for (int i = 0; i < 8; i++) {
            listPixLeave << pixLeave.copy(i * (pixLeave.width() / 8), 0, pixLeave.width() / 8, pixLeave.height());
        }

        update();
    }
}
