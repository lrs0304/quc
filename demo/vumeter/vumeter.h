#ifndef VUMETER_H
#define VUMETER_H

/**
 * 音量条控件 作者:来源于网络 整理:feiyangqingyun(QQ:517216493) 2016-10-8
 */

#include <QWidget>

#ifdef quc
#if (QT_VERSION < QT_VERSION_CHECK(5,7,0))
#include <QtDesigner/QDesignerExportWidget>
#else
#include <QtUiPlugin/QDesignerExportWidget>
#endif

class QDESIGNER_WIDGET_EXPORT VUMeter : public QWidget
        #else
class VUMeter : public QWidget
        #endif

{
    Q_OBJECT
    Q_PROPERTY(double minValue READ getMinValue WRITE setMinValue)
    Q_PROPERTY(double maxValue READ getMaxValue WRITE setMaxValue)
    Q_PROPERTY(double leftValue READ getLeftValue WRITE setLeftValue)
    Q_PROPERTY(double rightValue READ getRightValue WRITE setRightValue)

    Q_PROPERTY(QColor colorBg READ getColorBg WRITE setColorBg)
    Q_PROPERTY(QColor colorValue READ getColorValue WRITE setColorValue)
    Q_PROPERTY(QColor colorLow READ getColorLow WRITE setColorLow)
    Q_PROPERTY(QColor colorHigh READ getColorHigh WRITE setColorHigh)

public:
    explicit VUMeter(QWidget *parent = 0);
    ~VUMeter();

protected:
    void paintEvent(QPaintEvent *);
    void drawBorder(QPainter *painter);
    void drawBar(QPainter *painter);
    void drawValue(QPainter *painter);

private:
    double minValue;        //最小值
    double maxValue;        //最大值
    double leftValue;       //左边值
    double rightValue;      //右边值

    QColor colorBg;         //背景颜色
    QColor colorValue;      //值颜色
    QColor colorHigh;       //大值颜色
    QColor colorLow;        //小值颜色

public:
    double getMinValue()    const;
    double getMaxValue()    const;
    double getLeftValue()   const;
    double getRightValue()  const;

    QColor getColorBg()     const;
    QColor getColorValue()  const;
    QColor getColorLow()    const;
    QColor getColorHigh()   const;

    QSize sizeHint()        const;
    QSize minimumSizeHint() const;

public Q_SLOTS:
    void setMinValue(double minValue);
    void setMaxValue(double maxValue);
    void setLeftValue(double leftValue);
    void setRightValue(double rightValue);

    void setColorBg(const QColor &colorBg);
    void setColorValue(const QColor &colorValue);
    void setColorHigh(const QColor &colorHigh);
    void setColorLow(const QColor &colorLow);

Q_SIGNALS:
    void valueLChanged(double);
    void valueRChanged(double);
};

#endif
