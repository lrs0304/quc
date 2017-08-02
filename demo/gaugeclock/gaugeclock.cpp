#pragma execution_character_set("utf-8")

#include "gaugeclock.h"
#include "qpainter.h"
#include "qtimer.h"
#include "qdatetime.h"
#include "qmath.h"
#include "qaction.h"
#include "qprocess.h"
#include "qdebug.h"

GaugeClock::GaugeClock(QWidget *parent): QWidget(parent)
{
    action_secondstyle = new QAction("弹簧效果", this);
    connect(action_secondstyle, SIGNAL(triggered(bool)), this, SLOT(doAction()));
    this->addAction(action_secondstyle);

    this->setContextMenuPolicy(Qt::ActionsContextMenu);

    crownColorStart = QColor(255, 255, 255);
    crownColorEnd = QColor(166, 166, 166);

    foreground = QColor(255, 255, 255);
    background = QColor(65, 65, 65);

    pointerHourColor = QColor(160, 160, 160);
    pointerMinColor = QColor(160, 160, 160);
    pointerSecColor = QColor(160, 160, 160);

    timer = new QTimer(this);
    timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));
    timer->start();

    timerSpring = new QTimer(this);
    timerSpring->setInterval(30);
    connect(timerSpring, SIGNAL(timeout()), this, SLOT(updateSpring()));
    angleSpring = 6.0 * (sec + (double)msec / 1000);

    setSecondStyle(SecondStyle_Normal);
    updateTime();

    setFont(QFont("Arial", 9));
}

GaugeClock::~GaugeClock()
{
    if (timer->isActive()) {
        timer->stop();
    }

    if (timerSpring->isActive()) {
        timerSpring->stop();
    }
}

void GaugeClock::paintEvent(QPaintEvent *)
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
    //绘制时钟指针
    drawHour(&painter);
    //绘制分钟指针
    drawMin(&painter);
    //绘制秒钟指针
    drawSec(&painter);
    //绘制中心盖板
    drawDot(&painter);
}

void GaugeClock::drawCrown(QPainter *painter)
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

void GaugeClock::drawBg(QPainter *painter)
{
    int radius = 92;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(background);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void GaugeClock::drawScale(QPainter *painter)
{
    int radius = 90;
    painter->save();
    painter->setPen(foreground);
    QPen pen = painter->pen();
    pen.setCapStyle(Qt::RoundCap);

    for (int i = 0; i <= 60; i++) {
        if (i % 5 == 0) {
            pen.setWidthF(1.5);
            painter->setPen(pen);
            painter->drawLine(0, radius - 10, 0, radius);
        } else {
            pen.setWidthF(0.5);
            painter->setPen(pen);
            painter->drawLine(0, radius - 5, 0, radius);
        }

        painter->rotate(6);
    }

    painter->restore();
}

void GaugeClock::drawScaleNum(QPainter *painter)
{
    int radius = 70;
    painter->save();
    painter->setPen(foreground);

    double startRad = 60 * (M_PI / 180);
    double deltaRad = 30 * (M_PI / 180);

    for (int i = 0; i < 12; i++) {
        double sina = sin(startRad - i * deltaRad);
        double cosa = cos(startRad - i * deltaRad);
        QString strValue = QString("%1").arg(i + 1);

        double textWidth = fontMetrics().width(strValue);
        double textHeight = fontMetrics().height();
        int x = radius * cosa - textWidth / 2;
        int y = -radius * sina + textHeight / 4;
        painter->drawText(x, y, strValue);
    }

    painter->restore();
}

void GaugeClock::drawHour(QPainter *painter)
{
    painter->save();
    QPolygon pts;
    pts.setPoints(4, -3, 8, 3, 8, 2, -40, -2, -40);
    QPen pen = painter->pen();
    pen.setCapStyle(Qt::RoundCap);
    painter->rotate(30.0 * ((hour + min / 60.0)));
    painter->setPen(pointerHourColor);
    painter->setBrush(pointerHourColor);
    painter->drawConvexPolygon(pts);
    painter->restore();
}

void GaugeClock::drawMin(QPainter *painter)
{
    painter->save();
    QPolygon pts;
    pts.setPoints(4, -2, 8, 2, 8, 1, -60, -1, -60);
    QPen pen = painter->pen();
    pen.setCapStyle(Qt::RoundCap);
    painter->rotate(6.0 * (min + sec / 60.0));
    painter->setPen(pointerMinColor);
    painter->setBrush(pointerMinColor);
    painter->drawConvexPolygon(pts);
    painter->restore();
}

void GaugeClock::drawSec(QPainter *painter)
{
    if (secondStyle == SecondStyle_Hide) {
        return;
    }

    painter->save();
    QPolygon pts;
    pts.setPoints(3, -1, 10, 1, 10, 0, -70);
    QPen pen = painter->pen();
    pen.setCapStyle(Qt::RoundCap);
    painter->rotate(angleSpring);
    painter->setPen(pointerSecColor);
    painter->setBrush(pointerSecColor);
    painter->drawConvexPolygon(pts);
    painter->restore();
}

void GaugeClock::drawDot(QPainter *painter)
{
    painter->save();
    QConicalGradient coneGradient(0, 0, -90.0);
    coneGradient.setColorAt(0.0, background);
    coneGradient.setColorAt(0.5, foreground);
    coneGradient.setColorAt(1.0, background);
    painter->setOpacity(0.9);
    painter->setPen(Qt::NoPen);
    painter->setBrush(coneGradient);
    painter->drawEllipse(-5, -5, 10, 10);
    painter->restore();
}

void GaugeClock::doAction()
{
    QAction *action = (QAction *)sender();
    QString str = action->text();

    if (str == "弹簧效果") {
        action->setText("连续效果");
        setSecondStyle(SecondStyle_Spring);
    } else if (str == "连续效果") {
        action->setText("隐藏效果");
        setSecondStyle(SecondStyle_Continue);
    } else if (str == "隐藏效果") {
        action->setText("普通效果");
        setSecondStyle(SecondStyle_Hide);
    } else if (str == "普通效果") {
        action->setText("弹簧效果");
        setSecondStyle(SecondStyle_Normal);
    }
}

void GaugeClock::updateTime()
{
    QTime now = QTime::currentTime();
    hour = now.hour();
    min = now.minute();
    sec = now.second();
    msec = now.msec();

    if (secondStyle != SecondStyle_Hide) {
        angleSpring = 6.0 * (sec + (double)msec / 1000);

        if (secondStyle == SecondStyle_Spring) {
            angleSpring += 5;
            timerSpring->start();
        }
    }

    update();
}

void GaugeClock::updateSpring()
{
    angleSpring = 6.0 * (sec + (double)msec / 1000);
    update();
    timerSpring->stop();
}

GaugeClock::SecondStyle GaugeClock::getSecondStyle() const
{
    return this->secondStyle;
}

QColor GaugeClock::getCrownColorStart() const
{
    return this->crownColorStart;
}

QColor GaugeClock::getCrownColorEnd() const
{
    return this->crownColorEnd;
}

QColor GaugeClock::getForeground() const
{
    return this->foreground;
}

QColor GaugeClock::getBackground() const
{
    return this->background;
}

QColor GaugeClock::getPointerHourColor() const
{
    return this->pointerHourColor;
}

QColor GaugeClock::getPointerMinColor() const
{
    return this->pointerMinColor;
}

QColor GaugeClock::getPointerSecColor() const
{
    return this->pointerSecColor;
}

QSize GaugeClock::sizeHint() const
{
    return QSize(200, 200);
}

QSize GaugeClock::minimumSizeHint() const
{
    return QSize(50, 50);
}

void GaugeClock::setSecondStyle(GaugeClock::SecondStyle secondStyle)
{
    this->secondStyle = secondStyle;

    if (secondStyle == SecondStyle_Continue) {
        timer->setInterval(100);
    } else {
        timer->setInterval(1000);
    }

    if (secondStyle == SecondStyle_Spring) {
        action_secondstyle->setText("连续效果");
    } else if (secondStyle == SecondStyle_Continue) {
        action_secondstyle->setText("隐藏效果");
    } else if (secondStyle == SecondStyle_Hide) {
        action_secondstyle->setText("普通效果");
    } else if (secondStyle == SecondStyle_Normal) {
        action_secondstyle->setText("弹簧效果");
        updateTime();
        return;
    }

    update();
}

void GaugeClock::setSystemDateTime(QString year, QString month, QString day, QString hour, QString min, QString sec)
{
#ifdef Q_OS_WIN
    QProcess p(0);
    p.start("cmd");
    p.waitForStarted();
    p.write(QString("date %1-%2-%3\n").arg(year).arg(month).arg(day).toLatin1());
    p.closeWriteChannel();
    p.waitForFinished(1000);
    p.close();
    p.start("cmd");
    p.waitForStarted();
    p.write(QString("time %1:%2:%3.00\n").arg(hour).arg(min).arg(sec).toLatin1());
    p.closeWriteChannel();
    p.waitForFinished(1000);
    p.close();
#else
    QString cmd = QString("date %1%2%3%4%5.%6").arg(month).arg(day).arg(hour).arg(min).arg(year).arg(sec);
    system(cmd.toLatin1());
    system("hwclock -w");
#endif
}

void GaugeClock::setCrownColorStart(const QColor &crownColorStart)
{
    if (this->crownColorStart != crownColorStart) {
        this->crownColorStart = crownColorStart;
        update();
    }
}

void GaugeClock::setCrownColorEnd(const QColor &crownColorEnd)
{
    if (this->crownColorEnd != crownColorEnd) {
        this->crownColorEnd = crownColorEnd;
        update();
    }
}

void GaugeClock::setForeground(const QColor &foreground)
{
    if (this->foreground != foreground) {
        this->foreground = foreground;
        update();
    }
}

void GaugeClock::setBackground(const QColor &background)
{
    if (this->background != background) {
        this->background = background;
        update();
    }
}

void GaugeClock::setPointerHourColor(const QColor &pointerHourColor)
{
    if (this->pointerHourColor != pointerHourColor) {
        this->pointerHourColor = pointerHourColor;
        update();
    }
}

void GaugeClock::setPointerMinColor(const QColor &pointerMinColor)
{
    if (this->pointerMinColor != pointerMinColor) {
        this->pointerMinColor = pointerMinColor;
        update();
    }
}

void GaugeClock::setPointerSecColor(const QColor &pointerSecColor)
{
    if (this->pointerSecColor != pointerSecColor) {
        this->pointerSecColor = pointerSecColor;
        update();
    }
}
