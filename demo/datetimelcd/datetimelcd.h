#ifndef DATETIMELCD_H
#define DATETIMELCD_H

/**
 * 当前时间LCD控件 作者:feiyangqingyun(QQ:517216493) 2016-11-25
 * 1:可设置时间字符串格式
 * 2:可设置中间点分隔符是否闪烁
 * 3:可实时显示当前时间
 */

#include <QLCDNumber>

#ifdef quc
#if (QT_VERSION < QT_VERSION_CHECK(5,7,0))
#include <QtDesigner/QDesignerExportWidget>
#else
#include <QtUiPlugin/QDesignerExportWidget>
#endif

class QDESIGNER_WIDGET_EXPORT DateTimeLcd : public QLCDNumber
#else
class DateTimeLcd : public QLCDNumber
#endif

{
    Q_OBJECT
    Q_PROPERTY(bool dotHide READ getDotHide WRITE setDotHide)
    Q_PROPERTY(QString format READ getFormat WRITE setFormat)
    Q_PROPERTY(int digitCount READ getDigitCount WRITE setDigitCount)

public:
    explicit DateTimeLcd(QWidget *parent = 0);
    ~DateTimeLcd();

private:
    bool dotHide;
    QString format;
    int digitCount;
    QTimer *timer;

public:
    bool getDotHide()               const;
    QString getFormat()             const;
    int getDigitCount()             const;

    QSize sizeHint()                const;
    QSize minimumSizeHint()         const;

public slots:
    void start(int interval = 1000);
    void setDateTime();
    void setDotHide(bool dotHide);
    void setFormat(const QString &format);
};

#endif // DATETIMELCD_H
