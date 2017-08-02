#ifndef COLORCOMBOBOX_H
#define COLORCOMBOBOX_H

/**
 * 颜色下拉框控件 作者:feiyangqingyun(QQ:517216493) 2016-12-28
 * 1:支持内置所有颜色下拉选择
 */

#include <QComboBox>

#ifdef quc
#if (QT_VERSION < QT_VERSION_CHECK(5,7,0))
#include <QtDesigner/QDesignerExportWidget>
#else
#include <QtUiPlugin/QDesignerExportWidget>
#endif

class QDESIGNER_WIDGET_EXPORT ColorComboBox : public QComboBox
#else
class ColorComboBox : public QComboBox
#endif

{
    Q_OBJECT
    Q_PROPERTY(bool showColorName READ getShowColorName WRITE setShowColorName)

public:
    explicit ColorComboBox(QWidget *parent = 0);

private:
    bool showColorName;             //是否显示颜色名称

private slots:
    void doChanged(int index);

public:
    bool getShowColorName()         const;

public slots:
    void init();
    void setShowColorName(bool showColorName);

Q_SIGNALS:
    void currentItemChanged(const QString &item);
};

#endif // COLORCOMBOBOX_H
