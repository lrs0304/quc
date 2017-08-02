#pragma execution_character_set("utf-8")

#include "progressbarwait.h"
#include "qpainter.h"
#include "qtimer.h"
#include "qmath.h"
#include "qdebug.h"

ProgressBarWait::ProgressBarWait(QWidget *parent) : QWidget(parent)
{
    clockWise = true;
	showPercent = false;
	currentValue = 0;
	maxValue = 10;
	interval = 100;

	barStyle = BarStyle_Line;
	background = QColor(255, 255, 255);
	foreground = QColor(100, 184, 255);

	resizeEvent(NULL);

	timer = new QTimer(this);
	timer->setInterval(interval);
	connect(timer, SIGNAL(timeout()), this, SLOT(updateValue()));
	timer->start();
}

ProgressBarWait::~ProgressBarWait()
{
	if (timer->isActive()) {
		timer->stop();
	}
}

void ProgressBarWait::resizeEvent(QResizeEvent *)
{
	if (barStyle == BarStyle_DoubleCircle) {
		int radius = 200;
		minRadius = radius / 10;
		maxRadius = radius / 5;
		offsetRadius = radius / 30;
		leftRadius = minRadius;
		rightRadius = maxRadius;
		leftIncrease = true;
		rightIncrease = false;
	}
}

void ProgressBarWait::paintEvent(QPaintEvent *)
{
	int width = this->width();
	int height = this->height();
    int side = qMin(width, height);

	//绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
	QPainter painter(this);
	painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
	painter.translate(width / 2, height / 2);	
	painter.scale(side / 200.0, side / 200.0);

	if (barStyle == BarStyle_Arc) {
		drawArc(&painter);
	} else if (barStyle == BarStyle_RoundCircle) {
		drawRoundCircle(&painter);
	} else if (barStyle == BarStyle_Pie) {
		drawPie(&painter);
	} else if (barStyle == BarStyle_Line) {
		drawLine(&painter);
	} else if (barStyle == BarStyle_Ring) {
		drawRing(&painter);
	} else if (barStyle == BarStyle_SingleCircle) {
		drawSingleCircle(&painter);
	} else if (barStyle == BarStyle_DoubleCircle) {
		drawDoubleCircle(&painter);
	}

	if (showPercent) {
		drawText(&painter);
	}
}

void ProgressBarWait::drawArc(QPainter *painter)
{
	painter->save();
	painter->setPen(Qt::NoPen);

	//计算中心点坐标
	int centerX = 0;
	int centerY = 0;
	int radius = 99;
	int radiusBig = radius / 2;
	int radiusSmall = radius / 6;
	double currentangle = currentValue * (360 / (maxValue + 1));

    if (clockWise) {
		currentangle = -currentangle;
	}

	//绘制八卦大圆1
	painter->setBrush(foreground);
	QPainterPath pathBig1(QPointF(centerX + radius * cos(degreesToRadians(currentangle)),
	                              centerY - radius * sin(degreesToRadians(currentangle))));
	pathBig1.arcTo(centerX - radius, centerY - radius, radius * 2, radius * 2, currentangle, 180);
	pathBig1.arcTo(centerX + radiusBig * cos(degreesToRadians(currentangle + 180)) - radiusBig,
	               centerY - radiusBig * sin(degreesToRadians(currentangle + 180)) - radiusBig,
	               radiusBig * 2, radiusBig * 2, currentangle + 180, 180);
	pathBig1.arcTo(centerX + radiusBig * cos(degreesToRadians(currentangle)) - radiusBig,
	               centerY - radiusBig * sin(degreesToRadians(currentangle)) - radiusBig,
	               radiusBig * 2, radiusBig * 2, currentangle + 180, -180
	              );
	painter->drawPath(pathBig1);

	//绘制八卦大圆2
	painter->setBrush(background);
	QPainterPath pathBig2(QPointF(centerX + radius * cos(degreesToRadians(currentangle)),
	                              centerY - radius * sin(degreesToRadians(currentangle))));
	pathBig2.arcTo(centerX - radius, centerY - radius, radius * 2, radius * 2, currentangle, -180);
	pathBig2.arcTo(centerX + radiusBig * cos(degreesToRadians(currentangle + 180)) - radiusBig,
	               centerY - radiusBig * sin(degreesToRadians(currentangle + 180)) - radiusBig,
	               radiusBig * 2, radiusBig * 2, currentangle + 180, 180);
	pathBig2.arcTo(centerX + radiusBig * cos(degreesToRadians(currentangle)) - radiusBig,
	               centerY - radiusBig * sin(degreesToRadians(currentangle)) - radiusBig,
	               radiusBig * 2, radiusBig * 2, currentangle + 180, -180
	              );
	painter->drawPath(pathBig2);

	//绘制八卦小圆1
	painter->setBrush(foreground);
	QPainterPath pathSmall1;
	pathSmall1.addEllipse(centerX + radiusBig * cos(degreesToRadians(currentangle)) - radiusSmall,
	                      centerY - radiusBig * sin(degreesToRadians(currentangle)) - radiusSmall,
	                      radiusSmall * 2, radiusSmall * 2);
	painter->drawPath(pathSmall1);

	//绘制八卦小圆2
	painter->setBrush(background);
	QPainterPath pathSmall2;
	pathSmall2.addEllipse(centerX + radiusBig * cos(degreesToRadians(180 + currentangle)) - radiusSmall,
	                      centerY - radiusBig * sin(degreesToRadians(180 + currentangle)) - radiusSmall,
	                      radiusSmall * 2, radiusSmall * 2);
	painter->drawPath(pathSmall2);

	painter->restore();
}

void ProgressBarWait::drawRoundCircle(QPainter *painter)
{
	painter->save();
	painter->setPen(Qt::NoPen);

	int radius = 99;
	int minRadius = radius / 6;
	double angleStep = 360.0 / maxValue;
	double alpha = (double)1 / maxValue;

    if (!clockWise) {
		angleStep = -angleStep;
	}

	//计算中心点坐标
	int centerX = 0;
	int centerY = 0;
	double centerRadius = radius / 1.2;

	for (int i = 0; i < maxValue; i++) {
		double angle = (currentValue + i) * angleStep;
		double initX = centerRadius * cos(degreesToRadians(angle)) + centerX;
		double initY = centerRadius * sin(degreesToRadians(angle)) + centerY;

		int value = i * alpha * 255;
		value = value < 30 ? 30 : value;

		foreground.setAlpha(value);
		painter->setBrush(foreground);
		painter->drawEllipse(initX - minRadius, initY - minRadius, minRadius * 2, minRadius * 2);
	}

	painter->restore();
}

void ProgressBarWait::drawPie(QPainter *painter)
{
	int radius = 99;
	painter->save();

	//绘制背景圆
	painter->setPen(Qt::NoPen);
	painter->setBrush(background);
	painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);

	// 扇形起始角度
	int startAngle = (360 / (maxValue + 1)) * currentValue * 16;
	// 扇形覆盖范围
	int spanAngle = 60 * 16;
	//绘制扇形
	painter->setBrush(foreground);

    if (clockWise) {
		startAngle = -startAngle;
	}

	painter->drawPie(-radius, -radius, radius * 2, radius * 2, startAngle, spanAngle);

	painter->restore();
}

void ProgressBarWait::drawLine(QPainter *painter)
{
	int radius = 95;
	//这个Y轴坐标控制线条的高度,默认为半径的一半,值越大线条越短
	int initY = 50;

	painter->save();
	painter->setBrush(Qt::NoBrush);
	QPen pen = painter->pen();
	pen.setWidth(10);
	pen.setCapStyle(Qt::RoundCap);

	double angleStep = 360.0 / maxValue;
	double alpha = (double)1 / maxValue;

    if (!clockWise) {
		angleStep = -angleStep;
	}

	for (int i = 0; i <= maxValue; i++) {
		int value = (currentValue - i) * alpha * 255;

		if (value < 0) {
			value = value + 255;
		}

		value = value < 30 ? 30 : value;

		foreground.setAlpha(value);
		pen.setColor(foreground);
		painter->setPen(pen);
		painter->drawLine(0, initY, 0, radius);
		painter->rotate(angleStep);
	}

	painter->restore();
}

void ProgressBarWait::drawRing(QPainter *painter)
{
	int radius = 99;
	painter->save();
	painter->setPen(Qt::NoPen);

	QRectF rect(-radius, -radius, radius * 2, radius * 2);
	int arcHeight = 30;
	QPainterPath subPath;
	subPath.addEllipse(rect.adjusted(arcHeight, arcHeight, -arcHeight, -arcHeight));

	//当前扇形起始角度
	int startAngle = (360 / (maxValue + 1)) * currentValue;
	//当前扇形覆盖范围
	int spanAngle = 90;
	QPainterPath currentPath;

    if (clockWise) {
		currentPath.arcTo(rect, -startAngle, spanAngle);
	} else {
		currentPath.arcTo(rect, startAngle, spanAngle);
	}

	//其余扇形的起始角度为当前扇形的起始+覆盖范围
    if (clockWise) {
		startAngle = startAngle - spanAngle;
	} else {
		startAngle = startAngle + spanAngle;
	}

	//其余扇形的覆盖范围为 360 - 当前扇形的覆盖范围
	spanAngle = 360 - spanAngle;
	QPainterPath otherPath;

    if (clockWise) {
		otherPath.arcTo(rect, -startAngle, spanAngle);
	} else {
		otherPath.arcTo(rect, startAngle, spanAngle);
	}

	painter->setBrush(foreground);
	painter->drawPath(currentPath - subPath);
	painter->setBrush(background);
	painter->drawPath(otherPath - subPath);

	painter->restore();
}

void ProgressBarWait::drawSingleCircle(QPainter *painter)
{
	int radius = currentValue * 10;
	painter->save();
	painter->setPen(Qt::NoPen);
	painter->setBrush(foreground);
	painter->drawEllipse(QPoint(0, 0), radius, radius);
	painter->restore();
}

void ProgressBarWait::drawDoubleCircle(QPainter *painter)
{
	//如果圆半径小于最小半径则需要递增,半径大于最大半径则需要递减
	if (leftRadius <= minRadius) {
		leftIncrease = true;
	} else if (leftRadius >= maxRadius) {
		leftIncrease = false;
	}

	if (rightRadius <= minRadius) {
		rightIncrease = true;
	} else if (rightRadius >= maxRadius) {
		rightIncrease = false;
	}

	if (leftIncrease) {
		leftRadius += offsetRadius;
	} else {
		leftRadius -= offsetRadius;
	}

	if (rightIncrease) {
		rightRadius += offsetRadius;
	} else {
		rightRadius -= offsetRadius;
	}

	int radius = 50;

	painter->save();
	painter->setPen(Qt::NoPen);

	//绘制左边圆
	painter->setBrush(foreground);
	painter->drawEllipse(QPointF(-radius, 0), leftRadius, leftRadius);

	//绘制右边圆
	painter->setBrush(background);
	painter->drawEllipse(QPointF(radius, 0), rightRadius, rightRadius);

	painter->restore();
}

void ProgressBarWait::drawText(QPainter *painter)
{
	int radius = 100;
	painter->save();
	painter->setFont(QFont("Arial", 30, QFont::Bold, false));
	painter->setPen(foreground);
	QRect rect(-radius, -radius, radius * 2, radius * 2);
	painter->drawText(rect, Qt::AlignCenter, QString("%1%").arg(currentValue * (100 / maxValue)));
	painter->restore();
}

double ProgressBarWait::degreesToRadians(double degrees)
{
	return degrees * (M_PI / 180);
}

void ProgressBarWait::updateValue()
{
	if (currentValue < maxValue) {
		currentValue++;
	} else {
		currentValue = 0;
	}

	update();
}

bool ProgressBarWait::getClockWise() const
{
	return this->clockWise;
}

bool ProgressBarWait::getShowPercent() const
{
	return this->showPercent;
}

int ProgressBarWait::getCurrentValue() const
{
	return this->currentValue;
}

int ProgressBarWait::getMaxValue() const
{
	return this->maxValue;
}

int ProgressBarWait::getInterval() const
{
	return this->interval;
}

ProgressBarWait::BarStyle ProgressBarWait::getBarStyle() const
{
	return this->barStyle;
}

QColor ProgressBarWait::getBackground() const
{
	return this->background;
}

QColor ProgressBarWait::getForeground() const
{
	return this->foreground;
}

QSize ProgressBarWait::sizeHint() const
{
	return QSize(100, 100);
}

QSize ProgressBarWait::minimumSizeHint() const
{
	return QSize(20, 20);
}

void ProgressBarWait::setClockWise(bool clockWise)
{
    if (this->clockWise != clockWise){
        this->clockWise = clockWise;
        update();
    }
}

void ProgressBarWait::setShowPercent(bool showPercent)
{
    if (this->showPercent != showPercent){
        this->showPercent = showPercent;
        update();
    }
}

void ProgressBarWait::setCurrentValue(int currentValue)
{
    if (this->currentValue != currentValue){
        this->currentValue = currentValue;
        update();
    }
}

void ProgressBarWait::setMaxValue(int maxValue)
{
    if (this->maxValue != maxValue){
        this->maxValue = maxValue;
        this->currentValue = 0;
        update();
    }
}

void ProgressBarWait::setInterval(int interval)
{
    if (this->interval != interval){
        this->interval = interval;
        timer->setInterval(interval);
        update();
    }
}

void ProgressBarWait::setBarStyle(ProgressBarWait::BarStyle barStyle)
{
    if (this->barStyle != barStyle){
        this->barStyle = barStyle;
        update();
    }
}

void ProgressBarWait::setBackground(const QColor &background)
{
    if (this->background != background){
        this->background = background;
        update();
    }
}

void ProgressBarWait::setForeground(const QColor &foreground)
{
    if (this->foreground != foreground){
        this->foreground = foreground;
        update();
    }
}
