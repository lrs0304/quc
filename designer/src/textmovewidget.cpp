#pragma execution_character_set("utf-8")

#include "textmovewidget.h"
#include "qpainter.h"
#include "qtimer.h"
#include "qlabel.h"
#include "qdebug.h"

TextMoveWidget::TextMoveWidget(QWidget *parent) : QWidget(parent)
{
    setAutoFillBackground(true);

    text = "0123456789";
    step = 2;
    interval = 20;

    foreground = QColor(100, 184, 255);
    background = QColor(22, 22, 22);

    mouseHoverStop = false;
    moveStyle = MoveStyle_LeftAndRight;

    mouseHover = false;
    moveRight = true;
    initX = 0;
    initY = 0;

    labText = new QLabel(this);
    labText->setAlignment(Qt::AlignVCenter);    
    labText->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    timer = new QTimer(this);
    timer->setInterval(interval);
    connect(timer, SIGNAL(timeout()), this, SLOT(updatePos()));
    timer->start();

    setText(text);
    setForeground(foreground);
    setBackground(background);
}

TextMoveWidget::~TextMoveWidget()
{
    if (timer->isActive()) {
        timer->stop();
    }
}

void TextMoveWidget::resizeEvent(QResizeEvent *)
{
    initY = (height() - fontMetrics().height()) / 2;
}

void TextMoveWidget::enterEvent(QEvent *)
{
    mouseHover = true;

    if (mouseHoverStop) {
        QFont font = labText->font();
        font.setUnderline(true);
        labText->setFont(font);
        this->setCursor(Qt::PointingHandCursor);
    }
}

void TextMoveWidget::leaveEvent(QEvent *)
{
    mouseHover = false;

    if (mouseHoverStop) {
        QFont font = labText->font();
        font.setUnderline(false);
        labText->setFont(font);
        this->setCursor(Qt::ArrowCursor);
    }
}

void TextMoveWidget::updatePos()
{
    if (mouseHoverStop && mouseHover) {
        return;
    }

    int textWidth = this->fontMetrics().width(text);

    if (moveStyle == MoveStyle_LeftAndRight) {
        if (textWidth <= width()) {
            if (initX + textWidth > width()) {
                moveRight = false;
            } else if (initX <= 0) {
                moveRight = true;
            }
        } else {
            if (initX == 10) {
                moveRight = false;
            } else if (initX <= width() - textWidth - 10) {
                moveRight = true;
            }
        }

        if (moveRight) {
            initX += step;
        } else {
            initX -= step;
        }

        labText->move(initX, initY);
    } else if (moveStyle == MoveStyle_LeftToRight) {
        if (initX > width()) {
            initX = -textWidth;
        }

        initX += step;
        labText->move(initX, initY);
    } else if (moveStyle == MoveStyle_RightToLeft) {
        if (initX < -textWidth) {
            initX = width();
        }

        initX -= step;
        labText->move(initX, initY);
    }
}

QString TextMoveWidget::getText() const
{
    return this->text;
}

int TextMoveWidget::getStep() const
{
    return this->step;
}

int TextMoveWidget::getInterval() const
{
    return this->interval;
}

bool TextMoveWidget::getMouseHoverStop() const
{
    return this->mouseHoverStop;
}

QColor TextMoveWidget::getForeground() const
{
    return this->foreground;
}

QColor TextMoveWidget::getBackground() const
{
    return this->background;
}

TextMoveWidget::MoveStyle TextMoveWidget::getMoveStyle() const
{
    return this->moveStyle;
}

QSize TextMoveWidget::sizeHint() const
{
    return QSize(200, 30);
}

QSize TextMoveWidget::minimumSizeHint() const
{
    return QSize(30, 10);
}

void TextMoveWidget::setText(const QString &text)
{
    if (this->text != text) {
        this->text = text;
        labText->setText(text);

        //自动拉伸标签载体尺寸
        int textWidth = fontMetrics().width(text);
        int textHeight = fontMetrics().height();
        labText->resize(QSize(textWidth + 15, textHeight + 5));

        if (moveStyle == MoveStyle_LeftAndRight) {
            initX = 0;
        } else if (moveStyle == MoveStyle_LeftToRight) {
            initX = -labText->width();
        } else if (moveStyle == MoveStyle_RightToLeft) {
            initX = width();
        }
    }
}

void TextMoveWidget::setStep(int step)
{
    if (this->step != step) {
        this->step = step;
    }
}

void TextMoveWidget::setInterval(int interval)
{
    if (this->interval != interval) {
        this->interval = interval;
        timer->setInterval(interval);
    }
}

void TextMoveWidget::setMouseHoverStop(bool mouseHoverStop)
{
    if (this->mouseHoverStop != mouseHoverStop) {
        this->mouseHoverStop = mouseHoverStop;
    }
}

void TextMoveWidget::setForeground(const QColor &foreground)
{
    if (this->foreground != foreground) {
        this->foreground = foreground;
        QPalette pt = labText->palette();
        pt.setColor(QPalette::Foreground, foreground);
        labText->setPalette(pt);
    }
}

void TextMoveWidget::setBackground(const QColor &background)
{
    if (this->background != background) {
        this->background = background;
        QPalette pt = this->palette();
        pt.setColor(QPalette::Background, background);
        this->setPalette(pt);
    }
}

void TextMoveWidget::setMoveStyle(TextMoveWidget::MoveStyle moveStyle)
{
    if (this->moveStyle != moveStyle) {
        this->moveStyle = moveStyle;
    }
}
