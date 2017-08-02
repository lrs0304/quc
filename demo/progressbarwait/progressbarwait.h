#ifndef PROGRESSBARWAIT_H
#define PROGRESSBARWAIT_H

/**
 * 等待进度条控件 作者:feiyangqingyun(QQ:517216493) 2016-10-28
 * 1:支持多种等待样式风格 圆弧状风格 旋转圆风格 三角圆弧 线条风格 圆环风格
 * 2:可设置范围值和当前值
 * 3:可设置前景色背景色
 * 4:可设置顺时针逆时针旋转
 * 5:支持任意大小缩放
 * 6:支持设置旋转速度间隔
 */

#include <QWidget>

#ifdef quc
#if (QT_VERSION < QT_VERSION_CHECK(5,7,0))
#include <QtDesigner/QDesignerExportWidget>
#else
#include <QtUiPlugin/QDesignerExportWidget>
#endif

class QDESIGNER_WIDGET_EXPORT ProgressBarWait : public QWidget
#else
class ProgressBarWait : public QWidget
#endif

{
	Q_OBJECT
	Q_ENUMS(BarStyle)

	Q_PROPERTY(bool clockWise READ getClockWise WRITE setClockWise)
	Q_PROPERTY(bool showPercent READ getShowPercent WRITE setShowPercent)

	Q_PROPERTY(int currentValue READ getCurrentValue WRITE setCurrentValue)
	Q_PROPERTY(int maxValue READ getMaxValue WRITE setMaxValue)
	Q_PROPERTY(int interval READ getInterval WRITE setInterval)

	Q_PROPERTY(BarStyle barStyle READ getBarStyle WRITE setBarStyle)
	Q_PROPERTY(QColor background READ getBackground WRITE setBackground)
	Q_PROPERTY(QColor foreground READ getForeground WRITE setForeground)

public:
	enum BarStyle {
		BarStyle_Arc = 0,           //圆弧状风格
		BarStyle_RoundCircle = 1,   //旋转圆风格
		BarStyle_Pie = 2,           //三角圆弧风格
		BarStyle_Line = 3,          //线条风格
		BarStyle_Ring = 4,          //圆环风格
		BarStyle_SingleCircle = 5,  //一个圆闪烁
		BarStyle_DoubleCircle = 6   //两个圆闪烁
	};

	ProgressBarWait(QWidget *parent = 0);
	~ProgressBarWait();

protected:
	void resizeEvent(QResizeEvent *);
	void paintEvent(QPaintEvent *);
	void drawArc(QPainter *painter);
	void drawRoundCircle(QPainter *painter);
	void drawPie(QPainter *painter);
	void drawLine(QPainter *painter);
	void drawRing(QPainter *painter);
	void drawSingleCircle(QPainter *painter);
	void drawDoubleCircle(QPainter *painter);
	void drawText(QPainter *painter);

private:
	bool clockWise;                 //顺时针逆时针
	bool showPercent;               //显示当前百分比
	int currentValue;               //当前值
	int maxValue;                   //最大值
	int interval;                   //旋转间隔

	int minRadius;                  //最小半径
	int maxRadius;                  //最大半径
	int offsetRadius;               //半径偏移量
	int leftRadius;                 //左边圆半径
	int rightRadius;                //右边圆半径
	bool leftIncrease;              //左边递增
	bool rightIncrease;             //右边递增

	BarStyle barStyle;              //样式
	QColor background;              //背景色
	QColor foreground;              //前景色

	QTimer *timer;                  //定时器绘制

private:
	double degreesToRadians(double value);

private slots:
	void updateValue();

public:
	bool getClockWise()             const;
	bool getShowPercent()           const;
	int getCurrentValue()           const;
	int getMaxValue()               const;
	int getInterval()               const;

	BarStyle getBarStyle()          const;
	QColor getBackground()          const;
	QColor getForeground()          const;

	QSize sizeHint()                const;
	QSize minimumSizeHint()         const;

public Q_SLOTS:
	//设置顺时针逆时针旋转
	void setClockWise(bool clockWise);
	//设置是否显示百分比
	void setShowPercent(bool showPercent);
	//设置当前值
	void setCurrentValue(int currentValue);
	//设置最大值
	void setMaxValue(int maxValue);
	//设置旋转速度间隔
	void setInterval(int interval);

	//设置样式
	void setBarStyle(BarStyle barStyle);
	//设置前景色
	void setBackground(const QColor &background);
	//设置前景色
	void setForeground(const QColor &foreground);
};

#endif // PROGRESSBARWAIT_H
