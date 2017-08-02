#pragma execution_character_set("utf-8")

#include "ledtext.h"
#include "qpainter.h"
#include "qdebug.h"

LedText::LedText(QWidget *parent) : QWidget(parent)
{
    text = "123456789";    
    step = 5;

    foreground = QColor(100, 184, 255);
    background = QColor(22, 22, 22);
}

void LedText::paintEvent(QPaintEvent *)
{
    QString fontName = this->font().family();
    int fontSize = this->font().pointSize();

    QPixmap pix(width(), height());
    pix.fill(qRgb(0, 0, 0));
    QPainter painterPix(&pix);

    QImage image(160, 16, QImage::Format_MonoLSB);
    image.fill(qRgb(255, 255, 255));
    QPainter painterImg(&image);

    QFont font;
    font.setFamily(fontName);
    font.setPointSize(fontSize);

    QFont font2;
    font2.setFamily(fontName);
    font2.setPointSize(fontSize / 2);
    painterPix.setFont(font2);

    painterImg.setFont(font);
    painterImg.drawText(image.rect(), Qt::AlignLeft | Qt::AlignVCenter, text);

    int i, j, k, x, y;
    y = step;

    for (i = 0; i < 16; i++) {
        uchar *lineByte = image.scanLine(i);
        x = 0;

        for (j = 0; j < 20; j++) {
            uchar tp = lineByte[j];
            QString strBin;

            for (k = 0; k < 8; k++) {
                if (tp & 0x01) {
                    painterPix.setPen(background);
                    strBin += "0";
                } else {
                    painterPix.setPen(foreground);
                    strBin += "1";
                }

                painterPix.drawText(x, y, "●");
                x += step;
                tp >>= 1;
            }
        }

        y += step;
    }

    painterPix.end();
    painterImg.end();

    //将图片绘制到窗体
    QPainter painter(this);
    painter.drawPixmap(rect(), pix);
}

QString LedText::getText() const
{
    return this->text;
}

int LedText::getStep() const
{
    return this->step;
}

QColor LedText::getForeground() const
{
    return this->foreground;
}

QColor LedText::getBackground() const
{
    return this->background;
}

QSize LedText::sizeHint() const
{
    return QSize(200, 80);
}

QSize LedText::minimumSizeHint() const
{
    return QSize(20, 10);
}

void LedText::setText(const QString &text)
{
    if (this->text != text){
        this->text = text;
        update();
    }
}

void LedText::setStep(int step)
{
    if (this->step != step){
        this->step = step;
        update();
    }
}

void LedText::setForeground(const QColor &foreground)
{
    if (this->foreground != foreground){
        this->foreground = foreground;
        update();
    }
}

void LedText::setBackground(const QColor &background)
{
    if (this->background != background){
        this->background = background;
        update();
    }
}
