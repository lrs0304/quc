#ifndef WAVEPLOT_H
#define WAVEPLOT_H

/**
 * 正弦曲线控件 作者:feiyangqingyun(QQ:517216493) 2017-2-10
 */

#include <QWidget>

#ifdef quc
#if (QT_VERSION < QT_VERSION_CHECK(5,7,0))
#include <QtDesigner/QDesignerExportWidget>
#else
#include <QtUiPlugin/QDesignerExportWidget>
#endif

class QDESIGNER_WIDGET_EXPORT WavePlot : public QWidget
#else
class WavePlot : public QWidget
#endif

{
    Q_OBJECT
public:
    explicit WavePlot(QWidget *parent = 0);

protected:
    void resizeEvent(QResizeEvent *);
    void paintEvent(QPaintEvent *);

private:
    int pointCount;     //点个数
    QList<int> buffer;  //点坐标Y轴集合
    int flag1;          //变化因素1
    int flag2;          //变化因素2

public slots:
    void init();
    void clear();
    void changeFlag1(int flag1);
    void changeFlag2(int flag2);
};

#endif // WAVEPLOT_H
