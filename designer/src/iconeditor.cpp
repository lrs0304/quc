#include "iconeditor.h"
#include "qpainter.h"
#include "qevent.h"
#include "qdebug.h"

IconEditor::IconEditor(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);

    zoomFactor = 8;
    lineColor = QColor(200, 200, 200);
    penColor = Qt::black;

    iconImage = QImage(8, 8, QImage::Format_ARGB32);
    iconImage.fill(qRgba(0, 0, 0, 0));
}

void IconEditor::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        setImagePixel(event->pos(), true);
    } else if (event->button() == Qt::RightButton) {
        setImagePixel(event->pos(), false);
    }
}

void IconEditor::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        setImagePixel(event->pos(), true);
    } else if (event->buttons() & Qt::RightButton) {
        setImagePixel(event->pos(), false);
    }
}

void IconEditor::paintEvent(QPaintEvent *event)
{
    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //绘制背景
    //drawBg(&painter);
    //绘制图标
    drawIcon(&painter, event);
}

void IconEditor::drawBg(QPainter *painter)
{
    int size = 30;      //宫格大小
    int row = 0;        //当前行,用于切换第一个宫格颜色
    bool black = true;  //当前是否黑色背景

    for (int x = 0; x < width(); x += size) {
        for (int y = 0; y < height(); y += size) {
            QRect rect(x, y, size, size);
            if (black) {
                painter->fillRect(rect, QColor(220, 220, 220));
            } else {
                painter->fillRect(rect, QColor(255, 255, 255));
            }

            black = !black;
        }

        black = row % 2;
        row++;
    }
}

void IconEditor::drawIcon(QPainter *painter, QPaintEvent *event)
{
    //绘制网格线
    if (zoomFactor >= 3) {
        painter->setPen(lineColor);
        for (int i = 0; i <= iconImage.width(); ++i) {
            painter->drawLine(zoomFactor * i, 0, zoomFactor * i, zoomFactor * iconImage.height());
        }
        for (int j = 0; j <= iconImage.height(); ++j) {
            painter->drawLine(0, zoomFactor * j, zoomFactor * iconImage.width(), zoomFactor * j);
        }
    }

    //绘制宫格色块
    for (int i = 0; i < iconImage.width(); ++i) {
        for (int j = 0; j < iconImage.height(); ++j) {
            QRect rect = pixelRect(i, j);
            if (!event->region().intersected(rect).isEmpty()) {
                QColor color = QColor::fromRgba(iconImage.pixel(i, j));
                if (color.alpha() < 255) {
                    painter->fillRect(rect, Qt::white);
                }
                painter->fillRect(rect, color);
            }
        }
    }
}

void IconEditor::setImagePixel(const QPoint &pos, bool opaque)
{
    int i = pos.x() / zoomFactor;
    int j = pos.y() / zoomFactor;

    if (iconImage.rect().contains(i, j)) {
        if (opaque) {
            iconImage.setPixel(i, j, penColor.rgba());
        } else {
            iconImage.setPixel(i, j, qRgba(0, 0, 0, 0));
        }

        update(pixelRect(i, j));
    }
}

QRect IconEditor::pixelRect(int i, int j) const
{
    if (zoomFactor >= 3) {
        return QRect(zoomFactor * i + 1, zoomFactor * j + 1, zoomFactor - 1, zoomFactor - 1);
    } else {
        return QRect(zoomFactor * i, zoomFactor * j, zoomFactor, zoomFactor);
    }
}

int IconEditor::getZoomFactor() const
{
    return this->zoomFactor;
}

QColor IconEditor::getLineColor() const
{
    return this->lineColor;
}

QColor IconEditor::getPenColor() const
{
    return this->penColor;
}

QImage IconEditor::getIconImage() const
{
    return this->iconImage;
}

QSize IconEditor::sizeHint() const
{
    QSize size = zoomFactor * iconImage.size();

    if (zoomFactor >= 3) {
        size += QSize(1, 1);
    }

    return size;
}

QSize IconEditor::minimumSizeHint() const
{
    return QSize(30, 30);
}

void IconEditor::setZoomFactor(int zoomFactor)
{
    if (zoomFactor < 1) {
        this->zoomFactor = 1;
    }

    if (this->zoomFactor != zoomFactor) {
        this->zoomFactor = zoomFactor;
        update();
        updateGeometry();
    }
}

void IconEditor::setLineColor(const QColor &lineColor)
{
    if (this->lineColor != lineColor) {
        this->lineColor = lineColor;
        update();
    }
}

void IconEditor::setPenColor(const QColor &penColor)
{
    if (this->penColor != penColor) {
        this->penColor = penColor;
        update();
    }
}

void IconEditor::setIconImage(const QImage &iconImage)
{
    if (this->iconImage != iconImage) {
        this->iconImage = iconImage.convertToFormat(QImage::Format_ARGB32);
        update();
        updateGeometry();
    }
}

void IconEditor::setIconImage(const QString &iconFile)
{
    setIconImage(QImage(iconFile));
}

void IconEditor::saveIcon(const QString &file)
{
    QStringList list = file.split(".");
    if (list.count() > 0) {
        iconImage.save(file, list.last().toLatin1());
    }
}

void IconEditor::saveBg(const QString &file)
{
    QPixmap pix = QPixmap::grabWidget(this, this->geometry());
    QStringList list = file.split(".");
    if (list.count() > 0) {
        pix.save(file, list.last().toLatin1());
    }
}
