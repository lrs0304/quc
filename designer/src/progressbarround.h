#ifndef PROGRESSBARROUND_H
#define PROGRESSBARROUND_H

/**
 * 圆形进度条控件 作者:feiyangqingyun(QQ:517216493) 2016-10-16
 * 本控件来源于网络(原作者:不详(https://sourceforge.net/projects/qroundprogressbar/))
 * 1:支持三种风格样式 圆环风格/饼状风格/线条风格
 * 2:自动居中绘制显示
 * 3:可设置顺时针逆时针走向
 * 4:可设置起始进度位置
 * 5:可设置范围值
 * 6:可设置各种颜色
 * 7:可设置当前值
 * QPalette::Window         设置整个部件的背景
 * QPalette::Base           未填充进度区域的背景
 * QPalette::AlternateBase	文本显示所在的中间圆环的背景
 * QPalette::Shadow         未填充区域的前景色-边框色
 * QPalette::Highlight      填充进度条区域的背景色
 * QPalette::Text           在中心显示的文本色
 */

#include <QWidget>

#ifdef quc
#if (QT_VERSION < QT_VERSION_CHECK(5,7,0))
#include <QtDesigner/QDesignerExportWidget>
#else
#include <QtUiPlugin/QDesignerExportWidget>
#endif

class QDESIGNER_WIDGET_EXPORT ProgressBarRound : public QWidget
#else
class ProgressBarRound : public QWidget
#endif

{
    Q_OBJECT
    Q_ENUMS(BarStyle)

    Q_PROPERTY(double minValue READ getMinValue WRITE setMinValue)
    Q_PROPERTY(double maxValue READ getMaxValue WRITE setMaxValue)
    Q_PROPERTY(double value READ getValue WRITE setValue)
    Q_PROPERTY(int precision READ getPrecision WRITE setPrecision)

    Q_PROPERTY(double nullPosition READ getNullPosition WRITE setNullPosition)
    Q_PROPERTY(double outlinePenWidth READ getOutlinePenWidth WRITE setOutlinePenWidth)
    Q_PROPERTY(double dataPenWidth READ getDataPenWidth WRITE setDataPenWidth)

    Q_PROPERTY(BarStyle barStyle READ getBarStyle WRITE setBarStyle)
    Q_PROPERTY(QString format READ getFormat WRITE setFormat)
    Q_PROPERTY(bool clockWise READ getClockWise WRITE setClockWise)
    Q_PROPERTY(QGradientStops gradientData READ getGradientData WRITE setGradientData)

public:
    enum BarStyle {
        BarStyle_Donut = 0, //圆环风格
        BarStyle_Pie = 1,   //饼状风格
        BarStyle_Line = 2   //线条风格
    };

    explicit ProgressBarRound(QWidget *parent = 0);
    ~ProgressBarRound();

protected:
    void paintEvent(QPaintEvent *);
    void drawBg(QPainter *painter, const QRectF &baseRect);
    void drawBase(QPainter *painter, const QRectF &baseRect);
    void drawValue(QPainter *painter, const QRectF &baseRect);
    void calculateInnerRect(const QRectF &baseRect, double outerRadius, QRectF &innerRect, double &innerRadius);
    void drawInnerBackground(QPainter *painter, const QRectF &innerRect);
    void drawText(QPainter *painter, const QRectF &innerRect, double innerRadius);

private:
    QString valueToText(double value) const;
    void valueFormatChanged();
    void rebuildDataBrushIfNeeded();

private:
    static const int UF_VALUE = 1;
    static const int UF_PERCENT = 2;
    static const int UF_MAX = 4;
    int updateFlags;

public:
    static const int PositionLeft = 180;
    static const int PositionTop = 90;
    static const int PositionRight = 0;
    static const int PositionBottom = -90;

private:
    double minValue;                //最小值
    double maxValue;                //最大值
    double value;                   //目标值
    int precision;                  //精确度,小数点后几位

    double nullPosition;            //最小值位置
    double outlinePenWidth;         //外边框宽度
    double dataPenWidth;            //数据文本宽度

    BarStyle barStyle;              //样式
    QString format;                 //文本格式
    bool clockWise;                 //顺时针
    QGradientStops gradientData;    //颜色集合    

public:
    double getValue()               const;
    double getMinValue()            const;
    double getMaxValue()            const;
    int getPrecision()              const;

    double getNullPosition()        const;
    double getOutlinePenWidth()     const;
    double getDataPenWidth()        const;

    BarStyle getBarStyle()          const;
    QString	getFormat()             const;
    bool getClockWise()             const;
    QGradientStops getGradientData()const;    

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

    //设置精确度,小数点后几位
    void setPrecision(int precision);

    //设置最小值位置
    void setNullPosition(double nullPosition);
    //设置外边框宽度
    void setOutlinePenWidth(double outlinePenWidth);
    //设置数据文本宽度
    void setDataPenWidth(double dataPenWidth);

    //设置样式
    void setBarStyle(BarStyle barStyle);
    //设置格式
    void setFormat(const QString &format);

    //设置进度旋转方向
    void setClockWise(bool clockWise);
    //设置颜色集合
    void setGradientData(const QGradientStops &gradientData);    
};

#endif // PROGRESSBARROUND_H
