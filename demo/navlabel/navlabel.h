#ifndef NAVLABEL_H
#define NAVLABEL_H

/**
 * 导航标签控件 作者:feiyangqingyun(QQ:517216493) 2016-11-28
 * 1:可设置前景色和背景色
 * 2:可设置箭头方向 左右上下
 */

#include <QLabel>

#ifdef quc
#if (QT_VERSION < QT_VERSION_CHECK(5,7,0))
#include <QtDesigner/QDesignerExportWidget>
#else
#include <QtUiPlugin/QDesignerExportWidget>
#endif

class QDESIGNER_WIDGET_EXPORT NavLabel : public QLabel
#else
class NavLabel : public QLabel
#endif

{
	Q_OBJECT
    Q_ENUMS(ArrowStyle)

    Q_PROPERTY(ArrowStyle arrowStyle READ getArrowStyle WRITE setArrowStyle)
    Q_PROPERTY(QColor background READ getBackground WRITE setBackground)
    Q_PROPERTY(QColor foreground READ getForeground WRITE setForeground)

public:
	enum ArrowStyle {
		ArrowStyle_Left = 0,    //向左箭头
		ArrowStyle_Right = 1,   //向右箭头
		ArrowStyle_Top = 2,     //向上箭头
		ArrowStyle_Bottom = 3   //向下箭头
	};

	explicit NavLabel(QWidget *parent = 0);

protected:
	void paintEvent(QPaintEvent *);
	void drawBg(QPainter *painter);
	void drawText(QPainter *painter);

private:
    ArrowStyle arrowStyle;          //箭头样式
    QColor background;              //背景色
    QColor foreground;              //前景色
    QRect rect;                     //绘制区域

public:
    ArrowStyle getArrowStyle()      const;
    QColor getBackground()          const;
    QColor getForeground()          const;

    QSize sizeHint()                const;
    QSize minimumSizeHint()         const;

public Q_SLOTS:
	//设置箭头样式
	void setArrowStyle(ArrowStyle arrowStyle);
	//设置前景色
    void setBackground(const QColor &background);
	//设置前景色
    void setForeground(const QColor &foreground);
};

#endif // NAVLABEL_H
