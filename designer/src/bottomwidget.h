#ifndef BOTTOMWIDGET_H
#define BOTTOMWIDGET_H

/**
 * 通用底部信息栏 作者:feiyangqingyun(QQ:517216493) 2016-11-23
 * 1:可设置软件标题/版本/作者/当前用户/当前用户类型
 * 2:可实时显示已运行时间和当前时间
 * 3:可设置每个部件是否可见
 */

#include <QWidget>

class QLabel;

#ifdef quc
#if (QT_VERSION < QT_VERSION_CHECK(5,7,0))
#include <QtDesigner/QDesignerExportWidget>
#else
#include <QtUiPlugin/QDesignerExportWidget>
#endif

class QDESIGNER_WIDGET_EXPORT BottomWidget : public QWidget
        #else
class BottomWidget : public QWidget
        #endif

{
    Q_OBJECT
public:
    explicit BottomWidget(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *);

private:
    QString title;                  //标题
    QString version;                //版本
    QString author;                 //作者
    QString currentUserName;        //当前用户
    QString currentUserType;        //当前用户类型
    QString fontName;               //字体
    int fontSize;                   //字号
    bool lineFixedWidth;            //分隔符固定宽度

    int day;                        //天数
    int hour;                       //时钟数
    int minute;                     //分钟数
    int seconds;                    //秒钟数
    QTimer *timer;                  //定时器获取时间

    QLabel *labTitle;               //标题标签
    QLabel *labAuthor;              //作者标签
    QLabel *labUser;                //当前用户标签
    QLabel *labLive;                //已运行时间标签
    QLabel *labDateTime;            //当前时间标签

    bool labTitleVisible;           //标题标签是否可见
    bool labAuthorVisible;          //作者标签是否可见
    bool labUserVisible;            //当前用户标签是否可见
    bool labLiveVisible;            //已运行时间标签是否可见
    bool labDateTimeVisible;        //当前时间标签是否可见

private slots:
    void showTime();

public:
    QString getTitle()              const;
    QString getVersion()            const;
    QString getAuthor()             const;
    QString getCurrentUserName()    const;
    QString getCurrentUserType()    const;

public slots:
    void setLabTitleVisible(bool labTitleVisible);
    void setLabAuthorVisible(bool labAuthorVisible);
    void setLabUserVisible(bool labUserVisible);
    void setLabLiveVisible(bool labLiveVisible);
    void setLabDateTimeVisible(bool labDateTimeVisible);

    void setTitle(const QString &title);
    void setVersion(const QString &version);
    void setAuthor(const QString &author);
    void setCurrentUserName(const QString &currentUserName);
    void setCurrentUserType(const QString &currentUserType);
    void setFontName(const QString &fontName);
    void setFontSize(int fontSize);
    void setLineFixedWidth(bool lineFixedWidth);
    void start(int interval = 1000);
};

#endif // BOTTOMWIDGET_H
