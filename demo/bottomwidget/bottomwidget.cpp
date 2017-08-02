#pragma execution_character_set("utf-8")

#include "bottomwidget.h"
#include "qlabel.h"
#include "qframe.h"
#include "qboxlayout.h"
#include "qtimer.h"
#include "qdatetime.h"
#include "qstyle.h"
#include "qstyleoption.h"
#include "qpainter.h"

BottomWidget::BottomWidget(QWidget *parent) : QWidget(parent)
{
    title = "管理平台";
    version = "V1.0";
    author = "某某科技有限公司";
    currentUserName = "admin";
    currentUserType = "管理员";
    fontName = "Microsoft Yahei";
    fontSize = 9;
    lineFixedWidth = false;

    day = 0;
    hour = 0;
    minute = 0;
    seconds = 0;

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));

    labTitle = 0;
    labAuthor = 0;
    labUser = 0;
    labLive = 0;
    labDateTime = 0;

    labTitleVisible = true;
    labAuthorVisible = true;
    labUserVisible = true;
    labLiveVisible = true;
    labDateTimeVisible = true;
}

void BottomWidget::paintEvent(QPaintEvent *)
{
    //加上此代码让继承类样式起作用
    QStyleOption o;
    o.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &o, &p, this);
}

void BottomWidget::showTime()
{
    seconds++;

    if (seconds == 60) {
        minute++;
        seconds = 0;
    }

    if (minute == 60) {
        hour++;
        minute = 0;
    }

    if (hour == 24) {
        day++;
        hour = 0;
    }

    QDateTime now = QDateTime::currentDateTime();
    labLive->setText(QString("已运行: %1天%2时%3分%4秒").arg(day).arg(hour).arg(minute).arg(seconds));
    labDateTime->setText(now.toString("当前时间: yyyy年MM月dd日 HH:mm:ss"));
}

void BottomWidget::setLabTitleVisible(bool labTitleVisible)
{
    this->labTitleVisible = labTitleVisible;
}

void BottomWidget::setLabAuthorVisible(bool labAuthorVisible)
{
    this->labAuthorVisible = labAuthorVisible;
}

void BottomWidget::setLabUserVisible(bool labUserVisible)
{
    this->labUserVisible = labUserVisible;
}

void BottomWidget::setLabLiveVisible(bool labLiveVisible)
{
    this->labLiveVisible = labLiveVisible;
}

void BottomWidget::setLabDateTimeVisible(bool labDateTimeVisible)
{
    this->labDateTimeVisible = labDateTimeVisible;
}

void BottomWidget::setTitle(const QString &title)
{
    if (this->title != title) {
        this->title = title;
        if (labTitle != 0) {
            labTitle->setText(QString("欢迎使用%1 %2").arg(title).arg(version));
        }
    }
}

void BottomWidget::setVersion(const QString &version)
{
    if (this->version != version) {
        this->version = version;
        if (labTitle != 0) {
            labTitle->setText(QString("欢迎使用%1 %2").arg(title).arg(version));
        }
    }
}

void BottomWidget::setAuthor(const QString &author)
{
    if (this->author != author) {
        this->author = author;
        if (labAuthor != 0) {
            labAuthor->setText(QString("版权所有: %1").arg(author));
        }
    }
}

void BottomWidget::setCurrentUserName(const QString &currentUserName)
{
    if (this->currentUserName != currentUserName) {
        this->currentUserName = currentUserName;
        if (labUser != 0) {
            labUser->setText(QString("当前用户: %1【%2】").arg(currentUserName).arg(currentUserType));
        }
    }
}

void BottomWidget::setCurrentUserType(const QString &currentUserType)
{
    if (this->currentUserType != currentUserType) {
        this->currentUserType = currentUserType;
        if (labUser != 0) {
            labUser->setText(QString("当前用户: %1【%2】").arg(currentUserName).arg(currentUserType));
        }
    }
}

void BottomWidget::setFontName(const QString &fontName)
{
    this->fontName = fontName;
}

void BottomWidget::setFontSize(int fontSize)
{
    this->fontSize = fontSize;
}

void BottomWidget::setLineFixedWidth(bool lineFixedWidth)
{
    this->lineFixedWidth = lineFixedWidth;
}

void BottomWidget::start(int interval)
{
    labTitle = new QLabel;
    labTitle->setText(QString("欢迎使用%1 %2").arg(title).arg(version));

    labAuthor = new QLabel;
    labAuthor->setText(QString("版权所有: %1").arg(author));

    labUser = new QLabel;
    labUser->setText(QString("当前用户: %1【%2】").arg(currentUserName).arg(currentUserType));

    labLive = new QLabel;
    labDateTime = new QLabel;
    labDateTime->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    showTime();

    QFrame *line1 = new QFrame;
    line1->setFrameShape(QFrame::VLine);
    line1->setFrameShadow(QFrame::Sunken);

    QFrame *line2 = new QFrame;
    line2->setFrameShape(QFrame::VLine);
    line2->setFrameShadow(QFrame::Sunken);

    QFrame *line3 = new QFrame;
    line3->setFrameShape(QFrame::VLine);
    line3->setFrameShadow(QFrame::Sunken);

    QFrame *line4 = new QFrame;
    line4->setFrameShape(QFrame::VLine);
    line4->setFrameShadow(QFrame::Sunken);

    if (lineFixedWidth) {
        line1->setFixedWidth(1);
        line2->setFixedWidth(1);
        line3->setFixedWidth(1);
        line4->setFixedWidth(1);
    }

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setSpacing(6);
    layout->setContentsMargins(6, 6, 6, 6);

    if (labTitleVisible) {
        layout->addWidget(labTitle);
        layout->addWidget(line1);
    }

    if (labAuthorVisible) {
        layout->addWidget(labAuthor);
        layout->addWidget(line2);
    }

    if (labUserVisible) {
        layout->addWidget(labUser);
        layout->addWidget(line3);
    }

    if (labLiveVisible) {
        layout->addWidget(labLive);
        layout->addWidget(line4);
    }

    if (labDateTimeVisible) {
        layout->addWidget(labDateTime);
    }

    QFont font = QFont(fontName, fontSize);
    QList<QLabel *> labs = this->findChildren<QLabel *>();

    foreach (QLabel *lab, labs) {
        lab->setFont(font);
    }

    timer->start(interval);
}
