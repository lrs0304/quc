#include "combobox.h"
#include "qlistview.h"
#include "qdebug.h"

ComboBox::ComboBox(QWidget *parent) : QComboBox(parent)
{
    itemWidth = 5;
    itemHeight = 20;
    autoWidth = true;
    this->setView(new QListView());
}

void ComboBox::showEvent(QShowEvent *)
{
    if (autoWidth) {
        //自动计算所有元素,找到最长的元素
        QFontMetrics fm = this->fontMetrics();
        int count = this->count();
        for (int i = 0; i < count; i++) {
            int textWidth = fm.width(this->itemText(i));
            itemWidth = textWidth > itemWidth ? textWidth : itemWidth;
        }

        //宽度增加像素,因为有边距
        this->view()->setFixedWidth(itemWidth + 20);
    }
}

int ComboBox::getItemWidth() const
{
    return this->itemWidth;
}

int ComboBox::getItemHeight() const
{
    return this->itemHeight;
}

bool ComboBox::getAutoWidth() const
{
    return this->autoWidth;
}

void ComboBox::setItemWidth(int itemWidth)
{
    if (this->itemWidth != itemWidth) {
        this->itemWidth = itemWidth;
        if (!autoWidth) {
            this->view()->setFixedWidth(itemWidth);
        }
    }
}

void ComboBox::setItemHeight(int itemHeight)
{
    this->setStyleSheet(QString("QComboBox QAbstractItemView::item{min-height:%1px;}").arg(itemHeight));
}

void ComboBox::setAutoWidth(bool autoWidth)
{
    if (this->autoWidth != autoWidth) {
        this->autoWidth = autoWidth;
    }
}
