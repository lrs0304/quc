#ifndef WAVELINE_H
#define WAVELINE_H

/**
 * 直方波形图控件 作者:feiyangqingyun(QQ:517216493) 2016-11-6
 * 1:可设置范围值/当前值/步长/圆角角度
 * 2:可设置顶部滑块高度
 * 3:可设置背景颜色和线条颜色
 */

#include <QWidget>

#ifdef quc
#if (QT_VERSION < QT_VERSION_CHECK(5,7,0))
#include <QtDesigner/QDesignerExportWidget>
#else
#include <QtUiPlugin/QDesignerExportWidget>
#endif

class QDESIGNER_WIDGET_EXPORT WaveLine : public QWidget
#else
class WaveLine : public QWidget
#endif

{
    Q_OBJECT
    Q_PROPERTY(int maxValue READ getMaxValue WRITE setMaxValue)
    Q_PROPERTY(int step READ getStep WRITE setStep)
    Q_PROPERTY(int space READ getSpace WRITE setSpace)

    Q_PROPERTY(QColor bgColorStart READ getBgColorStart WRITE setBgColorStart)
    Q_PROPERTY(QColor bgColorEnd READ getBgColorEnd WRITE setBgColorEnd)
    Q_PROPERTY(QColor lineColor READ getLineColor WRITE setLineColor)

public:
    explicit WaveLine(QWidget *parent = 0);
    ~WaveLine();

protected:
    void paintEvent(QPaintEvent *);
    void drawBg(QPainter *painter);
    void drawLine(QPainter *painter);

private:
    int maxValue;                   //最大值
    int step;                       //步长
    int space;                      //间距

    QColor bgColorStart;            //背景渐变开始颜色
    QColor bgColorEnd;              //背景渐变结束颜色
    QColor lineColor;               //线条颜色

    QTimer *timer;                  //绘制定时器
    QVector<int> currentDataVec;    //当前数据集合
    QVector<int> dataVec;           //目标数据集合

private slots:
    void updateData();

public:
    int getMaxValue()               const;
    int getStep()                   const;
    int getSpace()                  const;

    QColor getBgColorStart()        const;
    QColor getBgColorEnd()          const;
    QColor getLineColor()           const;

    QSize sizeHint()                const;
    QSize minimumSizeHint()         const;

public slots:
    //设置数据
    void setData(const QVector<int> &dataVec);

    //设置最大值
    void setMaxValue(int maxValue);
    //设置步长
    void setStep(int step);
    //设置间距
    void setSpace(int space);

    //设置背景颜色
    void setBgColorStart(const QColor &bgColorStart);
    void setBgColorEnd(const QColor &bgColorEnd);

    //设置线条颜色
    void setLineColor(const QColor &lineColor);
};

#endif // WAVELINE_H
