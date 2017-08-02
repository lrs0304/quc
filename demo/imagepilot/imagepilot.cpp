#pragma execution_character_set("utf-8")

#include "imagepilot.h"
#include "qpainter.h"

ImagePilot::ImagePilot(QWidget *parent) : QWidget(parent)
{
	pilotStyle = PilotStyle_Blue;
	imgFile = ":/image/pilot_blue.png";
}

void ImagePilot::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	painter.setRenderHints(QPainter::SmoothPixmapTransform);
    QImage img(imgFile);
	painter.drawImage(rect(), img);
}

ImagePilot::PilotStyle ImagePilot::getPilotStyle() const
{
	return this->pilotStyle;
}

QString ImagePilot::getImgFile() const
{
	return this->imgFile;
}

QSize ImagePilot::sizeHint() const
{
	return QSize(200, 180);
}

QSize ImagePilot::minimumSizeHint() const
{
	return QSize(40, 36);
}

void ImagePilot::setPilotStyle(ImagePilot::PilotStyle pilotStyle)
{
    if (this->pilotStyle != pilotStyle){
        this->pilotStyle = pilotStyle;

        if (pilotStyle == PilotStyle_Blue) {
            imgFile = ":/image/pilot_blue.png";
        } else if (pilotStyle == PilotStyle_Gray) {
            imgFile = ":/image/pilot_gray.png";
        } else if (pilotStyle == PilotStyle_Green) {
            imgFile = ":/image/pilot_green.png";
        } else if (pilotStyle == PilotStyle_Red) {
            imgFile = ":/image/pilot_red.png";
        } else if (pilotStyle == PilotStyle_Yellow) {
            imgFile = ":/image/pilot_yellow.png";
        }

        update();
    }
}

void ImagePilot::setImage(QString imgFile)
{
    if (this->imgFile != imgFile){
        this->imgFile = imgFile;
        update();
    }
}
