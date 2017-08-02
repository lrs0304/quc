#ifndef TEXTMOVEWIDGET_H
#define TEXTMOVEWIDGET_H

/**
 * 跑马灯控件 作者:feiyangqingyun(QQ:517216493) 2016-11-30
 * 1:支持三种风格样式 左右来回滚动/从左滚动到右/从右滚动到左
 * 2:支持鼠标悬停停止滚动
 * 3:可设置前景色背景色
 * 4:可设置滚动的文本
 * 5:可设置定时器间隔
 */

#include <QWidget>

class QLabel;

#ifdef quc
#if (QT_VERSION < QT_VERSION_CHECK(5,7,0))
#include <QtDesigner/QDesignerExportWidget>
#else
#include <QtUiPlugin/QDesignerExportWidget>
#endif

class QDESIGNER_WIDGET_EXPORT TextMoveWidget : public QWidget
#else
class TextMoveWidget : public QWidget
#endif

{
    Q_OBJECT
    Q_ENUMS(MoveStyle)

    Q_PROPERTY(QString text READ getText WRITE setText)
    Q_PROPERTY(int step READ getStep WRITE setStep)
    Q_PROPERTY(int interval READ getInterval WRITE setInterval)
    Q_PROPERTY(bool mouseHoverStop READ getMouseHoverStop WRITE setMouseHoverStop)

    Q_PROPERTY(QColor foreground READ getForeground WRITE setForeground)
    Q_PROPERTY(QColor background READ getBackground WRITE setBackground)

    Q_PROPERTY(MoveStyle moveStyle READ getMoveStyle WRITE setMoveStyle)

public:
    enum MoveStyle {
        MoveStyle_LeftAndRight = 0, //左右来回滚动
        MoveStyle_LeftToRight = 1,  //从左滚动到右
        MoveStyle_RightToLeft = 2   //从右滚动到左
    };

    explicit TextMoveWidget(QWidget *parent = 0);
    ~TextMoveWidget();

protected:
    void resizeEvent(QResizeEvent *);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);

private:
    QString text;                   //滚动文本
    int step;                       //每次移动的步长
    int interval;                   //定时器间隔
    bool mouseHoverStop;            //鼠标悬停停止

    QColor foreground;              //前景色
    QColor background;              //背景色

    MoveStyle moveStyle;            //滚动样式

    bool mouseHover;                //鼠标是否悬停
    bool moveRight;                 //是否往右移动
    int initX;                      //当前X轴坐标
    int initY;                      //当前Y轴坐标
    QLabel *labText;                //显示文字的标签
    QTimer *timer;                  //定时器绘制

private slots:
    void updatePos();

public:
    QString getText()               const;
    int getStep()                   const;
    int getInterval()               const;
    bool getMouseHoverStop()        const;

    QColor getForeground()          const;
    QColor getBackground()          const;

    MoveStyle getMoveStyle()        const;

    QSize sizeHint()                const;
    QSize minimumSizeHint()         const;

public Q_SLOTS:
    //设置文本
    void setText(const QString &text);
    //设置步长
    void setStep(int step);
    //设置间隔
    void setInterval(int interval);
    //设置鼠标悬停停止滚动
    void setMouseHoverStop(bool mouseHoverStop);

    //设置前景色
    void setForeground(const QColor &foreground);
    //设置背景色
    void setBackground(const QColor &background);

    //设置滚动样式
    void setMoveStyle(MoveStyle moveStyle);
};

#endif // TEXTMOVEWIDGET_H
