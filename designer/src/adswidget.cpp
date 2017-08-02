#pragma execution_character_set("utf-8")

#include "adswidget.h"
#include "qevent.h"
#include "qlabel.h"
#include "qlayout.h"
#include "qtimer.h"
#include "qdebug.h"

AdsWidget::AdsWidget(QWidget *parent) : QWidget(parent)
{
    this->initWidget();
    this->initForm();
}

AdsWidget::~AdsWidget()
{
    if (timer->isActive()) {
        timer->stop();
    }
}

bool AdsWidget::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress) {
        if (obj->inherits("QLabel")) {
            changedAds((QLabel *)obj);
        }
    }

    return QWidget::eventFilter(obj, event);
}

void AdsWidget::initWidget()
{
    QVBoxLayout *verticalLayout = new QVBoxLayout(this);
    verticalLayout->setSpacing(0);
    verticalLayout->setContentsMargins(0, 0, 0, 0);

    widgetBg = new QWidget(this);
    widgetBg->setObjectName(QString::fromUtf8("widgetBg"));

    QGridLayout *gridLayout = new QGridLayout(widgetBg);
    gridLayout->setSpacing(0);
    gridLayout->setContentsMargins(0, 0, 0, 0);

    QSpacerItem *verticalSpacer = new QSpacerItem(20, 131, QSizePolicy::Minimum, QSizePolicy::Expanding);
    gridLayout->addItem(verticalSpacer, 0, 0, 1, 1);

    widgetBanner = new QWidget(widgetBg);
    widgetBanner->setObjectName(QString::fromUtf8("widgetBanner"));

    QHBoxLayout *horizontalLayout = new QHBoxLayout(widgetBanner);
    horizontalLayout->setSpacing(3);

    gridLayout->addWidget(widgetBanner, 1, 0, 1, 1);

    QSpacerItem *horizontalSpacer = new QSpacerItem(377, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    gridLayout->addItem(horizontalSpacer, 1, 1, 1, 1);

    verticalLayout->addWidget(widgetBg);
}

void AdsWidget::initForm()
{
    interval = 3000;
    bannerFixedSize = QSize(20, 20);
    bannerStyle = BannerStyle_Num;
    imageNames.clear();

    currentIndex = 0;

    timer = new QTimer(this);
    timer->setInterval(interval);
    connect(timer, SIGNAL(timeout()), this, SLOT(changedAds()));
    timer->start();
}

void AdsWidget::changedAds()
{
    if (names.count() == 0) {
        return;
    }

    if (currentIndex < names.count() - 1) {
        currentIndex++;
    } else {
        currentIndex = 0;
    }

    changedAds(labs.at(currentIndex));
}

void AdsWidget::changedAds(QLabel *lab)
{
    QString qss;
    QString qssCurrent;

    if (bannerStyle == BannerStyle_Min) {
        qss = "QLabel{background:#4380A8;}";
        qssCurrent = "QLabel{background:#084279;}";
    } else if (bannerStyle == BannerStyle_Num) {
        qss = "QLabel{color:#FFFFFF;background:rgba(0,0,0,40);}";
        qssCurrent = "QLabel{color:#FFFFFF;background:#0C7FC8;}";
    }

    //将当前广告指示器突出显示
    foreach (QLabel *currentLab, labs) {
        if (currentLab == lab) {
            currentLab->setStyleSheet(qssCurrent);
        } else {
            currentLab->setStyleSheet(qss);
        }
    }

    //更新索引和图片
    currentIndex = labs.indexOf(lab);
    widgetBg->setStyleSheet(QString("QWidget#widgetBg{border-image:url(%1);}").arg(names.at(currentIndex)));
}

int AdsWidget::getInterval() const
{
    return this->interval;
}

QSize AdsWidget::getBannerFixedSize() const
{
    return this->bannerFixedSize;
}

AdsWidget::BannerStyle AdsWidget::getBannerStyle() const
{
    return this->bannerStyle;
}

QString AdsWidget::getImageNames() const
{
    return this->imageNames;
}

QSize AdsWidget::sizeHint() const
{
    return QSize(200, 150);
}

QSize AdsWidget::minimumSizeHint() const
{
    return QSize(20, 15);
}

void AdsWidget::setInterval(int interval)
{
    if (this->interval != interval) {
        this->interval = interval;
        timer->setInterval(interval);
    }
}

void AdsWidget::setBannerFixedSize(const QSize &bannerFixedSize)
{
    if (this->bannerFixedSize != bannerFixedSize) {
        this->bannerFixedSize = bannerFixedSize;
        foreach (QLabel *lab, labs) {
            lab->setFixedSize(bannerFixedSize);
        }
    }
}

void AdsWidget::setBannerStyle(AdsWidget::BannerStyle bannerStyle)
{
    if (this->bannerStyle != bannerStyle) {
        this->bannerStyle = bannerStyle;

        foreach (QLabel *lab, labs) {
            if (bannerStyle == BannerStyle_Min) {
                lab->setText("");
            } else if (bannerStyle == BannerStyle_Num) {
                lab->setText(lab->text());
            }
        }
    }
}

void AdsWidget::setImageNames(const QString &imageNames)
{
    if (this->imageNames != imageNames) {
        this->imageNames = imageNames;

        //先清空原有所有元素
        qDeleteAll(widgetBanner->findChildren<QLabel *>());
        labs.clear();
        names.clear();

        //根据图片链表自动生成导航指示器和图片链表
        names = imageNames.split(";");
        for (int i = 0; i < names.count(); i++) {
            QLabel *lab = new QLabel;
            widgetBanner->layout()->addWidget(lab);
            lab->setFixedSize(bannerFixedSize);
            lab->setAlignment(Qt::AlignCenter);

            if (bannerStyle == BannerStyle_Num) {
                lab->setText(QString::number(i + 1));
            }

            lab->installEventFilter(this);

            labs.append(lab);
        }

        //立即显示第一张
        changedAds();
    }
}

