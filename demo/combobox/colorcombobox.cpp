#pragma execution_character_set("utf-8")

#include "colorcombobox.h"
#include "qdebug.h"

ColorComboBox::ColorComboBox(QWidget *parent) : QComboBox(parent)
{
    showColorName = false;
    connect(this, SIGNAL(currentIndexChanged(int)), this, SLOT(doChanged(int)));
}

void ColorComboBox::doChanged(int index)
{
    emit currentItemChanged(QColor::colorNames().at(index));
}

bool ColorComboBox::getShowColorName() const
{
    return this->showColorName;
}

void ColorComboBox::init()
{
    this->clear();
    QStringList colorList = QColor::colorNames();
    foreach (QString strColor, colorList) {
        QPixmap pix(this->iconSize());
        pix.fill(strColor);
        this->addItem(QIcon(pix), showColorName ? strColor : "");
    }
}

void ColorComboBox::setShowColorName(bool showColorName)
{
    if (this->showColorName != showColorName) {
        this->showColorName = showColorName;
    }
}
