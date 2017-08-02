#pragma execution_character_set("utf-8")

#include "progressbarround.h"
#include "qpainter.h"
#include "qdebug.h"

ProgressBarRound::ProgressBarRound(QWidget *parent) : QWidget(parent)
{
	value = 0;
	minValue = 0;
	maxValue = 100;
    precision = 0;

	nullPosition = 90;
    outlinePenWidth = 1;
    dataPenWidth = 1;

	barStyle = BarStyle_Donut;
    format = "%p%";
    clockWise = true;

    updateFlags = 2;

	setFont(QFont("Arial", 8));
}

ProgressBarRound::~ProgressBarRound()
{

}

void ProgressBarRound::paintEvent(QPaintEvent *)
{
	//半径取宽高的最小值
	double outerRadius = qMin(width(), height());
	//绘制区域在画面区域的基础上上下左右各减少一个像素,使得看起来完整
    QRectF baseRect(2, 2, outerRadius - 4, outerRadius - 4);

	//先将需要绘制的图形绘制到一张图片上,最后将图片绘制到屏幕
	QImage buffer(outerRadius, outerRadius, QImage::Format_ARGB32_Premultiplied);

	QPainter painter(&buffer);
	painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

	//绘制数据颜色集合
	rebuildDataBrushIfNeeded();
	//绘制背景
	drawBg(&painter, buffer.rect());
	//绘制外框
	drawBase(&painter, baseRect);
	//绘制数据
	drawValue(&painter, baseRect);

	//绘制中心
	double innerRadius(0);
	QRectF innerRect;
	calculateInnerRect(baseRect, outerRadius, innerRect, innerRadius);
	drawInnerBackground(&painter, innerRect);

	//绘制当前值
	drawText(&painter, innerRect, innerRadius);

	painter.end();

	QPainter p(this);
    p.setRenderHints(QPainter::SmoothPixmapTransform);
    p.fillRect(baseRect, palette().background());

	//改成居中绘制图片
	int pixX = rect().center().x() - buffer.width() / 2;
	int pixY = rect().center().y() - buffer.height() / 2;
	QPoint point(pixX, pixY);
	p.drawImage(point, buffer);
}

void ProgressBarRound::drawBg(QPainter *painter, const QRectF &baseRect)
{
    painter->fillRect(baseRect, palette().background());
}

void ProgressBarRound::drawBase(QPainter *painter, const QRectF &baseRect)
{
	switch (barStyle) {
		case BarStyle_Donut:
			painter->setPen(QPen(palette().shadow().color(), outlinePenWidth));
			painter->setBrush(palette().base());
			painter->drawEllipse(baseRect);
			break;

		case BarStyle_Pie:
			painter->setPen(QPen(palette().base().color(), outlinePenWidth));
			painter->setBrush(palette().base());
			painter->drawEllipse(baseRect);
			break;

		case BarStyle_Line:
			painter->setPen(QPen(palette().base().color(), outlinePenWidth));
			painter->setBrush(Qt::NoBrush);
			painter->drawEllipse(baseRect.adjusted(outlinePenWidth / 2, outlinePenWidth / 2, -outlinePenWidth / 2, -outlinePenWidth / 2));
			break;
	}
}

void ProgressBarRound::drawValue(QPainter *painter, const QRectF &baseRect)
{
	if (value == minValue) {
		return;
	}

	double arcLength = 360.0 / (maxValue - minValue) * value;

	//逆时针为顺时针分负数
    if (!clockWise) {
		arcLength = -arcLength;
	}

	if (barStyle == BarStyle_Line) {
		painter->setPen(QPen(palette().highlight().color(), dataPenWidth));
		painter->setBrush(Qt::NoBrush);
		painter->drawArc(baseRect.adjusted(outlinePenWidth / 2, outlinePenWidth / 2, -outlinePenWidth / 2, -outlinePenWidth / 2),
		                 nullPosition * 16, -arcLength * 16);
		return;
	}

	QPainterPath dataPath;
	dataPath.setFillRule(Qt::WindingFill);

	dataPath.moveTo(baseRect.center());
	dataPath.arcTo(baseRect, nullPosition, -arcLength);
	dataPath.lineTo(baseRect.center());

	painter->setBrush(palette().highlight());
	painter->setPen(QPen(palette().shadow().color(), dataPenWidth));
	painter->drawPath(dataPath);
}

void ProgressBarRound::calculateInnerRect(const QRectF &/*baseRect*/, double outerRadius, QRectF &innerRect, double &innerRadius)
{
	if (barStyle == BarStyle_Line) {
		innerRadius = outerRadius - outlinePenWidth;
	} else {
		innerRadius = outerRadius * 0.75;
	}

	double delta = (outerRadius - innerRadius) / 2;
	innerRect = QRectF(delta, delta, innerRadius, innerRadius);
}

void ProgressBarRound::drawInnerBackground(QPainter *painter, const QRectF &innerRect)
{
	if (barStyle == BarStyle_Donut) {
		painter->setBrush(palette().alternateBase());
		painter->drawEllipse(innerRect);
	}
}

void ProgressBarRound::drawText(QPainter *painter, const QRectF &innerRect, double innerRadius)
{
	if (format.isEmpty()) {
		return;
	}

	QFont f(font());
    f.setPixelSize(innerRadius * qMax(0.05, (0.35 - (double)precision * 0.08)));
	painter->setFont(f);

	QRectF textRect(innerRect);
	painter->setPen(palette().text().color());
	painter->drawText(textRect, Qt::AlignCenter, valueToText(value));
}

QString ProgressBarRound::valueToText(double value) const
{
	QString textToDraw(format);

	if (updateFlags & UF_VALUE) {
        textToDraw.replace("%v", QString::number(value, 'f', precision));
	}

	if (updateFlags & UF_PERCENT) {
		double procent = (value - minValue) / (maxValue - minValue) * 100.0;
        textToDraw.replace("%p", QString::number(procent, 'f', precision));
	}

	if (updateFlags & UF_MAX) {
        textToDraw.replace("%m", QString::number(maxValue - minValue + 1, 'f', precision));
	}

	return textToDraw;
}

void ProgressBarRound::valueFormatChanged()
{
	updateFlags = 0;

	if (format.contains("%v")) {
		updateFlags |= UF_VALUE;
	}

	if (format.contains("%p")) {
		updateFlags |= UF_PERCENT;
	}

	if (format.contains("%m")) {
		updateFlags |= UF_MAX;
	}

	update();
}

void ProgressBarRound::rebuildDataBrushIfNeeded()
{
	if (gradientData.count() == 0) {
		return;
	}

	QConicalGradient dataBrush;
	dataBrush.setCenter(0.5, 0.5);
	dataBrush.setCoordinateMode(QGradient::StretchToDeviceMode);

	for (int i = 0; i < gradientData.count(); i++) {
		dataBrush.setColorAt(1.0 - gradientData.at(i).first, gradientData.at(i).second);
	}

	dataBrush.setAngle(nullPosition);
	QPalette p(palette());
	p.setBrush(QPalette::Highlight, dataBrush);
	setPalette(p);
}

double ProgressBarRound::getValue() const
{
    return this->value;
}

double ProgressBarRound::getMinValue() const
{
    return this->minValue;
}

double ProgressBarRound::getMaxValue() const
{
    return this->maxValue;
}

int ProgressBarRound::getPrecision() const
{
    return this->precision;
}

double ProgressBarRound::getNullPosition() const
{
    return this->nullPosition;
}

double ProgressBarRound::getOutlinePenWidth() const
{
    return this->outlinePenWidth;
}

double ProgressBarRound::getDataPenWidth() const
{
    return this->dataPenWidth;
}

ProgressBarRound::BarStyle ProgressBarRound::getBarStyle() const
{
    return this->barStyle;
}

QString ProgressBarRound::getFormat() const
{
    return this->format;
}

bool ProgressBarRound::getClockWise() const
{
    return this->clockWise;
}

QGradientStops ProgressBarRound::getGradientData() const
{
    return this->gradientData;
}

QSize ProgressBarRound::sizeHint() const
{
    return QSize(100, 100);
}

QSize ProgressBarRound::minimumSizeHint() const
{
    return QSize(10, 10);
}

void ProgressBarRound::setRange(double minValue, double maxValue)
{
	this->minValue = minValue;
	this->maxValue = maxValue;

	if (this->maxValue < this->minValue) {
		qSwap(this->maxValue, this->minValue);
	}

	if (value < this->minValue) {
		value = this->minValue;
	} else if (value > this->maxValue) {
		value = this->maxValue;
	}

	update();
}

void ProgressBarRound::setRange(int minValue, int maxValue)
{
	setRange((double)minValue, (double)maxValue);
}

void ProgressBarRound::setMinValue(double minValue)
{
	setRange(minValue, maxValue);
}

void ProgressBarRound::setMaxValue(double maxValue)
{
	setRange(minValue, maxValue);
}

void ProgressBarRound::setValue(double value)
{
	//值小于最小值或者值大于最大值或者值和当前值一致则无需处理
	if (value < minValue || value > maxValue || value == this->value) {
		return;
	}

	this->value = value;
	update();
}

void ProgressBarRound::setValue(int value)
{
	setValue(double(value));
}

void ProgressBarRound::setPrecision(int precision)
{
    if (precision >= 0 && this->precision != precision) {
        this->precision = precision;
		valueFormatChanged();
	}
}

void ProgressBarRound::setNullPosition(double nullPosition)
{
	if (this->nullPosition != nullPosition) {
		this->nullPosition = nullPosition;
		update();
	}
}

void ProgressBarRound::setBarStyle(ProgressBarRound::BarStyle barStyle)
{
	if (this->barStyle != barStyle) {
		this->barStyle = barStyle;
		update();
	}
}

void ProgressBarRound::setFormat(const QString &format)
{
	if (this->format != format) {
		this->format = format;
		valueFormatChanged();
	}
}

void ProgressBarRound::setOutlinePenWidth(double outlinePenWidth)
{
    if (this->outlinePenWidth != outlinePenWidth) {
        this->outlinePenWidth = outlinePenWidth;
		update();
	}
}

void ProgressBarRound::setDataPenWidth(double dataPenWidth)
{
    if (this->dataPenWidth != dataPenWidth) {
        this->dataPenWidth = dataPenWidth;
		update();
	}
}

void ProgressBarRound::setClockWise(bool clockWise)
{
    if (this->clockWise != clockWise) {
        this->clockWise = clockWise;
		update();
	}
}

void ProgressBarRound::setGradientData(const QGradientStops &gradientData)
{
    if (this->gradientData != gradientData) {
        this->gradientData = gradientData;
        update();
    }
}
