#pragma execution_character_set("utf-8")

#include "imageview.h"
#include "qevent.h"
#include "qpainter.h"
#include "qtoolbutton.h"
#include "qtimer.h"
#include "qaction.h"
#include "qdir.h"
#include "qfiledialog.h"
#include "qdebug.h"

ImageNum::ImageNum(QWidget *parent) : QWidget(parent)
{
    totalNum = 0;
    currentIndex = -1;
    setFixedSize(160, 30);
}

void ImageNum::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    drawBg(&painter);
    drawText(&painter);
}

void ImageNum::drawBg(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(QColor(46, 132, 243));
    painter->drawRoundedRect(rect(), 2, 2);
    painter->restore();
}

void ImageNum::drawText(QPainter *painter)
{
    QString strText = QString("第 %1 张 / 共 %2 张").arg(currentIndex + 1).arg(totalNum);
    painter->save();
    painter->setPen(Qt::white);
    QFont textFont;
    textFont.setBold(true);
    painter->setFont(textFont);
    painter->drawText(rect(), Qt::AlignCenter, strText);
    painter->restore();
}

void ImageNum::setTotalNum(int totalNum)
{
    if (totalNum < 0) {
        this->totalNum = 0;
    } else {
        this->totalNum = totalNum;
    }

    this->currentIndex = 0;
    update();
}

void ImageNum::setCurrentIndex(int currentIndex)
{
    if (currentIndex < 0) {
        this->currentIndex = -1;
    } else {
        this->currentIndex = currentIndex;
    }

    update();
}

ImageView::ImageView(QWidget *parent) :	QWidget(parent)
{
    setStyleSheet(".QToolButton{background-color:rgba(0,0,0,0);border-style:none;}");

    bgColorStart = QColor(100, 100, 100);
    bgColorEnd = QColor(60, 60, 60);

    bottomSpace = 10;
    buttonSpace = 10;
    icoSize = QSize(65, 65);

    fade = false;
    fill = false;
    keyMove = false;

    totalNum = 0;
    currentIndex = -1;

    num = new ImageNum(this);
    connect(this, SIGNAL(totalNumChanged(int)), num, SLOT(setTotalNum(int)));
    connect(this, SIGNAL(currentIndexChanged(int)), num, SLOT(setCurrentIndex(int)));

    preButton = new QToolButton(this);
    nextButton = new QToolButton(this);

    preButton->setIconSize(icoSize);
    nextButton->setIconSize(icoSize);

    preButton->setIcon(QIcon(":/image/btn_pre_normal.png"));
    nextButton->setIcon(QIcon(":/image/btn_next_normal.png"));

    connect(preButton, SIGNAL(clicked()), this, SLOT(movePrevious()));
    connect(nextButton, SIGNAL(clicked()), this, SLOT(moveNext()));

    opacity = 1.0;
    timer = new QTimer(this);
    timer->setInterval(50);
    connect(timer, SIGNAL(timeout()), this, SLOT(doFading()));

    QAction *action_load = new QAction("载入", this);
    connect(action_load, SIGNAL(triggered(bool)), this, SLOT(load()));
    this->addAction(action_load);

    QAction *action_clear = new QAction("清空", this);
    connect(action_clear, SIGNAL(triggered(bool)), this, SLOT(clear()));
    this->addAction(action_clear);

    this->setContextMenuPolicy(Qt::ActionsContextMenu);
    calcGeo();
}

ImageView::~ImageView()
{
    if (timer->isActive()) {
        timer->stop();
    }
}

void ImageView::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    drawBg(&painter);

    if (totalNum > 0) {
        drawImage(&painter);
    }
}

void ImageView::drawBg(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient bgGradient(QPoint(0, 0), QPoint(0, height()));
    bgGradient.setColorAt(0.0, bgColorStart);
    bgGradient.setColorAt(1.0, bgColorEnd);
    painter->setBrush(bgGradient);
    painter->drawRect(rect());
    painter->restore();
}

void ImageView::drawImage(QPainter *painter)
{
    painter->save();
    painter->setOpacity(opacity);

    if (fill) {
        painter->drawImage(rect(), currentImage);
        painter->restore();
    } else {
        //按照比例自动居中绘制
        int imageWidth = currentImage.width();
        int imageHeight = currentImage.height();
        int imageX = rect().center().x() - imageWidth / 2;
        int imageY = rect().center().y() - imageHeight / 2;
        QPoint point(imageX, imageY);

        painter->drawImage(point, currentImage);
        painter->restore();
    }
}

void ImageView::keyPressEvent(QKeyEvent *keyEvent)
{
    if (keyEvent->key() == Qt::Key_Left || keyEvent->key() == Qt::Key_Up) {
        movePrevious();
    } else if (keyEvent->key() == Qt::Key_Right || keyEvent->key() == Qt::Key_Down) {
        moveNext();
    }
}

void ImageView::resizeEvent(QResizeEvent *)
{
    calcGeo();
}

void ImageView::showEvent(QShowEvent *)
{
    calcGeo();
}

void ImageView::calcGeo()
{
    QPoint prePoint(buttonSpace, (height() - preButton->height()) / 2);
    preButton->move(prePoint);

    QPoint nextPoint(width() - buttonSpace - preButton->width(), (height() - preButton->height()) / 2);
    nextButton->move(nextPoint);

    QPoint numPoint(width() / 2 - num->width() / 2, height() - bottomSpace - preButton->height() / 2 - num->height() / 2);
    num->move(numPoint);
}

void ImageView::doFading()
{
    opacity += 0.05;

    if (opacity > 1.0) {
        opacity = 1.0;
        timer->stop();
    }

    update();
}

QColor ImageView::getBgColorStart() const
{
    return this->bgColorStart;
}

QColor ImageView::getBgColorEnd() const
{
    return this->bgColorEnd;
}

int ImageView::getBottomSpace() const
{
    return this->bottomSpace;
}

int ImageView::getButtonSpace() const
{
    return this->buttonSpace;
}

QSize ImageView::getIcoSize() const
{
    return this->icoSize;
}

bool ImageView::getFill() const
{
    return this->fill;
}

bool ImageView::getFade() const
{
    return this->fade;
}

bool ImageView::getKeyMove() const
{
    return this->keyMove;
}

QSize ImageView::sizeHint() const
{
    return QSize(300, 150);
}

QSize ImageView::minimumSizeHint() const
{
    return QSize(10, 10);
}

void ImageView::load()
{
    QString strDir = QFileDialog::getExistingDirectory(this, "选择图片文件");

    if (!strDir.isEmpty()) {
        load(strDir);
    }
}

void ImageView::load(QString strFolder)
{
    QDir imageFolder(strFolder);
    imageFolder.setSorting(QDir::Time);

    if (imageFolder.exists()) {
        QStringList filter;
        filter << "*.png" << "*.jpg" << "*.gif" << "*.jpeg" << "*.bmp" ;
        QStringList imageList = imageFolder.entryList(filter);

        totalNum = imageList.count();
        currentIndex = -1;
        imageNames.clear();

        if (totalNum > 0) {
            foreach (QString strImage, imageList) {
                QString strFullPath = QString("%1/%2").arg(strFolder).arg(strImage);
                imageNames.append(strFullPath);
            }

            moveTo(0);
            emit totalNumChanged(totalNum);
        }
    }
}

void ImageView::clear()
{
    totalNum = 0;
    currentIndex = -1;
    imageNames.clear();
    update();

    emit totalNumChanged(totalNum);
    emit currentIndexChanged(currentIndex);
}

void ImageView::setBgColorStart(const QColor &bgColorStart)
{
    if (this->bgColorStart != bgColorStart) {
        this->bgColorStart = bgColorStart;
        update();
    }
}

void ImageView::setBgColorEnd(const QColor &bgColorEnd)
{
    if (this->bgColorEnd != bgColorEnd) {
        this->bgColorEnd = bgColorEnd;
        update();
    }
}

void ImageView::setBottomSpace(int bottomSpace)
{
    if (this->bottomSpace != bottomSpace) {
        this->bottomSpace = bottomSpace;
        update();
    }
}

void ImageView::setButtonSpace(int buttonSpace)
{
    if (this->buttonSpace != buttonSpace) {
        this->buttonSpace = buttonSpace;
        update();
    }
}

void ImageView::setIcoSize(const QSize &icoSize)
{
    if (this->icoSize != icoSize) {
        this->icoSize = icoSize;
        preButton->setIconSize(icoSize);
        nextButton->setIconSize(icoSize);
        calcGeo();
        update();
    }
}

void ImageView::setFill(bool fill)
{
    if (this->fill != fill) {
        this->fill = fill;
        update();
    }
}

void ImageView::setFade(bool fade)
{
    if (this->fade != fade) {
        this->fade = fade;
        update();
    }
}

void ImageView::setKeyMove(bool keyMove)
{
    if (this->keyMove != keyMove) {
        this->keyMove = keyMove;

        if (keyMove) {
            setFocusPolicy(Qt::StrongFocus);
        } else {
            setFocusPolicy(Qt::NoFocus);
        }
    }
}

void ImageView::moveFirst()
{
    int index = 0;

    if (currentIndex != index) {
        moveTo(index);
    }
}

void ImageView::moveLast()
{
    int index = totalNum - 1;

    if (currentIndex != index) {
        moveTo(index);
    }
}

void ImageView::movePrevious()
{
    if (currentIndex > 0) {
        currentIndex--;
        moveTo(currentIndex);
    }
}

void ImageView::moveNext()
{
    if (currentIndex < totalNum - 1) {
        currentIndex++;
        moveTo(currentIndex);
    }
}

void ImageView::moveTo(int index)
{
    if (totalNum == 0 || index > totalNum - 1) {
        return ;
    }

    currentIndex = index;
    currentImage = QImage(imageNames.at(currentIndex));
    emit currentIndexChanged(currentIndex);

    if (fade) {
        opacity = 0.0;
        timer->start();
    } else {
        update();
    }
}
