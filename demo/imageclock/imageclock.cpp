#pragma execution_character_set("utf-8")

#include "imageclock.h"
#include "qpainter.h"
#include "qtimer.h"
#include "qdatetime.h"
#include "qmath.h"
#include "qaction.h"
#include "qprocess.h"
#include "qdebug.h"

ImageClock::ImageClock(QWidget *parent): QWidget(parent)
{
	setFont(QFont("Microsoft Yahei", 9));

	QAction *action_trad = new QAction("黑色风格", this);
	connect(action_trad, SIGNAL(triggered(bool)), this, SLOT(doAction()));
	this->addAction(action_trad);

	QAction *action_system = new QAction("银色风格", this);
	connect(action_system, SIGNAL(triggered(bool)), this, SLOT(doAction()));
	this->addAction(action_system);

	QAction *action_modern = new QAction("红色风格", this);
	connect(action_modern, SIGNAL(triggered(bool)), this, SLOT(doAction()));
	this->addAction(action_modern);

	QAction *action_flower = new QAction("花瓣风格", this);
	connect(action_flower, SIGNAL(triggered(bool)), this, SLOT(doAction()));
	this->addAction(action_flower);

	action_secondstyle = new QAction("弹簧效果", this);
	connect(action_secondstyle, SIGNAL(triggered(bool)), this, SLOT(doAction()));
	this->addAction(action_secondstyle);

	this->setContextMenuPolicy(Qt::ActionsContextMenu);

	imageNames << "trad" << "system" << "modern" << "flower";

	timer = new QTimer(this);
	timer->setInterval(1000);
	connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));
	timer->start();

	timerSpring = new QTimer(this);
	timerSpring->setInterval(30);
	connect(timerSpring, SIGNAL(timeout()), this, SLOT(updateSpring()));
	angleSpring = 6.0 * (sec + (double)msec / 1000);

    setClockStyle(ClockStyle_System);
	setSecondStyle(SecondStyle_Normal);
	updateTime();
}

ImageClock::~ImageClock()
{
	if (timer->isActive()) {
		timer->stop();
	}

	if (timerSpring->isActive()) {
		timerSpring->stop();
	}
}

void ImageClock::paintEvent(QPaintEvent *)
{
	int width = this->width();
	int height = this->height();

	//绘制准备工作,启用反锯齿,启用图片平滑缩放
	QPainter painter(this);
	painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
	painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

	//绘制背景
	drawBg(&painter);

	painter.translate(width / 2, height / 2);

	//绘制时钟指针 尺寸：13×129
	drawHour(&painter);
	//绘制分钟指针 尺寸：13×129
	drawMin(&painter);
	//绘制秒钟指针 尺寸：13×129
	drawSec(&painter);
	//绘制中心盖板
	drawDot(&painter);
}

void ImageClock::drawBg(QPainter *painter)
{
	painter->save();
	int pixX = rect().center().x() - clockBg.width() / 2;
	int pixY = rect().center().y() - clockBg.height() / 2;
	QPoint point(pixX, pixY);
	painter->drawImage(point, clockBg);
	painter->drawImage(point, clockHighlights);
	painter->restore();
}

void ImageClock::drawHour(QPainter *painter)
{
	painter->save();
	painter->rotate(30.0 * ((hour + min / 60.0)));
	painter->drawImage(QRect(-6.5, -64.5, 13, 129), clockHour);
	painter->restore();
}

void ImageClock::drawMin(QPainter *painter)
{
	painter->save();
	painter->rotate(6.0 * (min + sec / 60.0));
	painter->drawImage(QRect(-6.5, -64.5, 13, 129), clockMin);
	painter->restore();
}

void ImageClock::drawSec(QPainter *painter)
{
	if (secondStyle == SecondStyle_Hide) {
		return;
	}

	painter->save();
	painter->rotate(angleSpring);
	painter->drawImage(QRect(-6.5, -64.5, 13, 129), clockSec);
	painter->restore();
}

void ImageClock::drawDot(QPainter *painter)
{
	painter->save();
	painter->drawImage(QRect(-6.5, -64.5, 13, 129), clockDot);
	painter->restore();
}

void ImageClock::doAction()
{
	QAction *action = (QAction *)sender();
	QString str = action->text();

	if (str == "黑色风格") {
		setClockStyle(ClockStyle_Trad);
	} else if (str == "银色风格") {
		setClockStyle(ClockStyle_System);
	} else if (str == "红色风格") {
		setClockStyle(ClockStyle_Modern);
	} else if (str == "花瓣风格") {
		setClockStyle(ClockStyle_Flower);
	} else if (str == "弹簧效果") {
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

void ImageClock::updateTime()
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

void ImageClock::updateSpring()
{
	angleSpring = 6.0 * (sec + (double)msec / 1000);
	update();
	timerSpring->stop();
}

ImageClock::ClockStyle ImageClock::getClockStyle() const
{
	return this->clockStyle;
}

ImageClock::SecondStyle ImageClock::getSecondStyle() const
{
	return this->secondStyle;
}

QSize ImageClock::sizeHint() const
{
	return QSize(130, 130);
}

QSize ImageClock::minimumSizeHint() const
{
	return QSize(130, 130);
}

void ImageClock::setClockStyle(ImageClock::ClockStyle clockStyle)
{
    if (this->clockStyle != clockStyle){
        QString imageName = imageNames.at(clockStyle);
        this->clockStyle = clockStyle;
        clockBg = QImage(QString(":/image/%1.png").arg(imageName));
        clockHour = QImage(QString(":/image/%1_h.png").arg(imageName));
        clockMin = QImage(QString(":/image/%1_m.png").arg(imageName));
        clockSec = QImage(QString(":/image/%1_s.png").arg(imageName));
        clockDot = QImage(QString(":/image/%1_dot.png").arg(imageName));
        clockHighlights = QImage(QString(":/image/%1_highlights.png").arg(imageName));
        update();
    }
}

void ImageClock::setSecondStyle(ImageClock::SecondStyle secondStyle)
{
    if (this->secondStyle != secondStyle){
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
}

void ImageClock::setSystemDateTime(QString year, QString month, QString day, QString hour, QString min, QString sec)
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
