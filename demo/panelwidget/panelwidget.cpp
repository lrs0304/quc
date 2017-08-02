#pragma execution_character_set("utf-8")

#include "panelwidget.h"
#include "qscrollarea.h"
#include "qframe.h"
#include "qboxlayout.h"

PanelWidget::PanelWidget(QWidget *parent) : QWidget(parent)
{
    scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);

    scrollAreaWidgetContents = new QWidget();
    scrollAreaWidgetContents->setGeometry(QRect(0, 0, 100, 100));

    verticalLayout = new QVBoxLayout(scrollAreaWidgetContents);
    verticalLayout->setSpacing(0);
    verticalLayout->setContentsMargins(0, 0, 0, 0);

    frame = new QFrame(scrollAreaWidgetContents);

    gridLayout = new QGridLayout(frame);
    gridLayout->setSpacing(0);

    verticalLayout->addWidget(frame);
    scrollArea->setWidget(scrollAreaWidgetContents);
}

void PanelWidget::resizeEvent(QResizeEvent *)
{
    scrollArea->resize(this->size());
}

QSize PanelWidget::sizeHint() const
{
    return QSize(300, 200);
}

QSize PanelWidget::minimumSizeHint() const
{
    return QSize(20, 20);
}

void PanelWidget::setWidget(QList<QWidget *> widgets, int columnCount)
{
    //先清空原有所有元素
    qDeleteAll(frame->findChildren<QWidget *>());

    int row = 0;
    int column = 0;
    int index = 0;

    foreach (QWidget *widget, widgets) {
        gridLayout->addWidget(widget, row, column);
        column++;
        index++;

        if (index % columnCount == 0) {
            row++;
            column = 0;
        }
    }

    row++;
    QSpacerItem *verticalSpacer = new QSpacerItem(1, 1, QSizePolicy::Minimum, QSizePolicy::Expanding);
    gridLayout->addItem(verticalSpacer, row, 0);
}

void PanelWidget::setBorder(int width, const QString &strColor)
{
    //增加滚动条样式
    QString bgColor = "#FFFFFF";//#0B68A2
    QString handleNormalColor = "#084871";
    QString handleHoverColor = "#1ABC9C";
    QString handlePressedColor = "#E74C3C";

    QStringList qss;
    qss.append(QString(".QScrollArea{border:%1px solid %2;}").arg(width).arg(strColor));

    //圆角角度
    int radius = 6;
    //指示器最小长度
    int min = 120;
    //滚动条最大长度
    int max = 12;
    //滚动条离背景间隔
    int padding = 0;

    //handle:指示器,滚动条拉动部分 add-page:滚动条拉动时增加的部分 sub-page:滚动条拉动时减少的部分 add-line:递增按钮 sub-line:递减按钮

    //横向滚动条部分
    qss.append(QString("QScrollBar:horizontal{background:%1;padding:%2px;border-radius:%3px;max-height:%4px;}")
               .arg(bgColor).arg(padding).arg(radius).arg(max));
    qss.append(QString("QScrollBar::handle:horizontal{background:%1;min-width:%2px;border-radius:%3px;}")
               .arg(handleNormalColor).arg(min).arg(radius));
    qss.append(QString("QScrollBar::handle:horizontal:hover{background:%1;}")
               .arg(handleHoverColor));
    qss.append(QString("QScrollBar::handle:horizontal:pressed{background:%1;}")
               .arg(handlePressedColor));
    qss.append(QString("QScrollBar::add-page:horizontal{background:none;}"));
    qss.append(QString("QScrollBar::sub-page:horizontal{background:none;}"));
    qss.append(QString("QScrollBar::add-line:horizontal{background:none;}"));
    qss.append(QString("QScrollBar::sub-line:horizontal{background:none;}"));

    //纵向滚动条部分
    qss.append(QString("QScrollBar:vertical{background:%1;padding:%2px;border-radius:%3px;max-width:%4px;}")
               .arg(bgColor).arg(padding).arg(radius).arg(max));
    qss.append(QString("QScrollBar::handle:vertical{background:%1;min-height:%2px;border-radius:%3px;}")
               .arg(handleNormalColor).arg(min).arg(radius));
    qss.append(QString("QScrollBar::handle:vertical:hover{background:%1;}")
               .arg(handleHoverColor));
    qss.append(QString("QScrollBar::handle:vertical:pressed{background:%1;}")
               .arg(handlePressedColor));
    qss.append(QString("QScrollBar::add-page:vertical{background:none;}"));
    qss.append(QString("QScrollBar::sub-page:vertical{background:none;}"));
    qss.append(QString("QScrollBar::add-line:vertical{background:none;}"));
    qss.append(QString("QScrollBar::sub-line:vertical{background:none;}"));

    scrollArea->setStyleSheet(qss.join(""));
}

void PanelWidget::setMargin(int left, int top, int right, int bottom)
{
    gridLayout->setContentsMargins(left, top, right, bottom);
}

void PanelWidget::setMargin(int margin)
{
    setMargin(margin, margin, margin, margin);
}

void PanelWidget::setSpacing(int space)
{
    gridLayout->setSpacing(space);
}

void PanelWidget::setFrame(int border, const QString &strColor)
{
    frame->setStyleSheet(QString(".QFrame{border:%1px;background-color:%2;}").arg(border).arg(strColor));
}
