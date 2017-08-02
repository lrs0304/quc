#ifndef GAUGESPEED_H
#define GAUGESPEED_H

/**
 * 速度仪表盘控件 作者:feiyangqingyun(QQ:517216493) 2016-12-31
 * 1:可设置范围值,支持负数值
 * 2:可设置精确度,最大支持小数点后3位
 * 3:可设置大刻度数量/小刻度数量
 * 4:可设置开始旋转角度/结束旋转角度
 * 5:可设置是否启用动画效果以及动画效果每次移动的步长
 * 6:可设置三色圆环占比例
 * 7:自适应窗体拉伸,刻度尺和文字自动缩放
 */

#include <QWidget>

class QLCDNumber;

#ifdef quc
#if (QT_VERSION < QT_VERSION_CHECK(5,7,0))
#include <QtDesigner/QDesignerExportWidget>
#else
#include <QtUiPlugin/QDesignerExportWidget>
#endif

class QDESIGNER_WIDGET_EXPORT GaugeSpeed : public QWidget
#else
class GaugeSpeed : public QWidget
#endif

{
    Q_OBJECT
    Q_PROPERTY(double minValue READ getMinValue WRITE setMinValue)
    Q_PROPERTY(double maxValue READ getMaxValue WRITE setMaxValue)
    Q_PROPERTY(double value READ getValue WRITE setValue)
    Q_PROPERTY(int precision READ getPrecision WRITE setPrecision)

    Q_PROPERTY(int scaleMajor READ getScaleMajor WRITE setScaleMajor)
    Q_PROPERTY(int scaleMinor READ getScaleMinor WRITE setScaleMinor)
    Q_PROPERTY(int startAngle READ getStartAngle WRITE setStartAngle)
    Q_PROPERTY(int endAngle READ getEndAngle WRITE setEndAngle)

    Q_PROPERTY(bool animation READ getAnimation WRITE setAnimation)
    Q_PROPERTY(double animationStep READ getAnimationStep WRITE setAnimationStep)

    Q_PROPERTY(int ringWidth READ getRingWidth WRITE setRingWidth)
    Q_PROPERTY(int ringStartPercent READ getRingStartPercent WRITE setRingStartPercent)
    Q_PROPERTY(int ringMidPercent READ getRingMidPercent WRITE setRingMidPercent)
    Q_PROPERTY(int ringEndPercent READ getRingEndPercent WRITE setRingEndPercent)

    Q_PROPERTY(QColor ringColorStart READ getRingColorStart WRITE setRingColorStart)
    Q_PROPERTY(QColor ringColorMid READ getRingColorMid WRITE setRingColorMid)
    Q_PROPERTY(QColor ringColorEnd READ getRingColorEnd WRITE setRingColorEnd)

    Q_PROPERTY(QColor pointerColor READ getPointerColor WRITE setPointerColor)
    Q_PROPERTY(QColor textColor READ getTextColor WRITE setTextColor)

public:
    explicit GaugeSpeed(QWidget *parent = 0);
    ~GaugeSpeed();

protected:
    void resizeEvent(QResizeEvent *);
    void paintEvent(QPaintEvent *);
    void drawRing(QPainter *painter);
    void drawScale(QPainter *painter);
    void drawScaleNum(QPainter *painter);
    void drawPointer(QPainter *painter);
    void drawText(QPainter *painter);

private slots:
    void updateValue();

private:    
    double maxValue;                //最小值
    double minValue;                //最大值
    double value;                   //目标值
    int precision;                  //精确度,小数点后几位

    int scaleMajor;                 //大刻度数量
    int scaleMinor;                 //小刻度数量
    int startAngle;                 //开始旋转角度
    int endAngle;                   //结束旋转角度

    bool animation;                 //是否启用动画显示
    double animationStep;           //动画显示时步长

    int ringWidth;                  //圆环宽度
    int ringStartPercent;           //第一圆环比例
    int ringMidPercent;             //第二圆环比例
    int ringEndPercent;             //第三圆环比例

    QColor ringColorStart;          //第一圆环颜色
    QColor ringColorMid;            //第二圆环颜色
    QColor ringColorEnd;            //第三圆环颜色

    QColor pointerColor;            //指针颜色
    QColor textColor;               //文字颜色

    bool reverse;                   //是否往回走
    double currentValue;            //当前值
    QTimer *timer;                  //定时器绘制动画
    QLCDNumber *lcd;                //数码管

public:   
    double getMinValue()            const;
    double getMaxValue()            const;
    double getValue()               const;
    int getPrecision()              const;

    int getScaleMajor()             const;
    int getScaleMinor()             const;
    int getStartAngle()             const;
    int getEndAngle()               const;

    bool getAnimation()             const;
    double getAnimationStep()       const;

    int getRingWidth()              const;
    int getRingStartPercent()       const;
    int getRingMidPercent()         const;
    int getRingEndPercent()         const;

    QColor getRingColorStart()      const;
    QColor getRingColorMid()        const;
    QColor getRingColorEnd()        const;

    QColor getPointerColor()        const;
    QColor getTextColor()           const;

    QSize sizeHint()                const;
    QSize minimumSizeHint()         const;

public Q_SLOTS:
    //设置范围值
    void setRange(double minValue, double maxValue);
    void setRange(int minValue, int maxValue);

    //设置最大最小值
    void setMinValue(double minValue);
    void setMaxValue(double maxValue);

    //设置目标值
    void setValue(double value);
    void setValue(int value);

    //设置精确度
    void setPrecision(int precision);

    //设置主刻度数量
    void setScaleMajor(int scaleMajor);
    //设置小刻度数量
    void setScaleMinor(int scaleMinor);
    //设置开始旋转角度
    void setStartAngle(int startAngle);
    //设置结束旋转角度
    void setEndAngle(int endAngle);

    //设置是否启用动画显示
    void setAnimation(bool animation);
    //设置动画显示的步长
    void setAnimationStep(double animationStep);

    //设置饼圆宽度
    void setRingWidth(int ringWidth);

    //设置三个圆环所占比例
    void setRingStartPercent(int ringStartPercent);
    void setRingMidPercent(int ringMidPercent);
    void setRingEndPercent(int ringEndPercent);

    //设置三个圆环颜色
    void setRingColorStart(const QColor &ringColorStart);
    void setRingColorMid(const QColor &ringColorMid);
    void setRingColorEnd(const QColor &ringColorEnd);

    //设置指针颜色
    void setPointerColor(const QColor &pointerColor);
    //设置文本颜色
    void setTextColor(const QColor &textColor);

Q_SIGNALS:
    void valueChanged(int value);
};

#endif //GAUGESPEED_H
