#ifndef FRMWAVEPLOT_H
#define FRMWAVEPLOT_H

#include <QWidget>

namespace Ui {
class frmWavePlot;
}

class frmWavePlot : public QWidget
{
    Q_OBJECT

public:
    explicit frmWavePlot(QWidget *parent = 0);
    ~frmWavePlot();

private:
    Ui::frmWavePlot *ui;
    QTimer *timer;

private slots:
    void updateValue();
    void on_horizontalSlider1_valueChanged(int value);
    void on_horizontalSlider2_valueChanged(int value);
    void on_horizontalSlider3_valueChanged(int value);
};

#endif // FRMWAVEPLOT_H
