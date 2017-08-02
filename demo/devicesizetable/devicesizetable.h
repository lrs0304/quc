#ifndef DEVICESIZETABLE_H
#define DEVICESIZETABLE_H

/**
 * 本地存储空间大小控件 作者:feiyangqingyun(QQ:517216493) 2016-11-30
 * 1:可自动加载本地存储设备的总容量/已用容量
 * 2:进度条显示已用容量
 * 3:支持所有操作系统
 * 4:增加U盘或者SD卡到达信号
 */

#include <QTableWidget>

class QProcess;

#ifdef quc
#if (QT_VERSION < QT_VERSION_CHECK(5,7,0))
#include <QtDesigner/QDesignerExportWidget>
#else
#include <QtUiPlugin/QDesignerExportWidget>
#endif

class QDESIGNER_WIDGET_EXPORT DeviceSizeTable : public QTableWidget
#else
class DeviceSizeTable : public QTableWidget
#endif

{
	Q_OBJECT
public:
	explicit DeviceSizeTable(QWidget *parent = 0);

private:
	QProcess *process;

private slots:
	void init();
	void readData();
    void checkSize(const QString &result, const QString &name);
    void insertSize(const QString &name, const QString &use, const QString &free, const QString &all, int percent);

public:
    QSize sizeHint()                const;
    QSize minimumSizeHint()         const;

public Q_SLOTS:
	void load();

Q_SIGNALS:
    void sdcardReceive(const QString &sdcardName);
    void udiskReceive(const QString &udiskName);
};

#endif // DEVICESIZETABLE_H
