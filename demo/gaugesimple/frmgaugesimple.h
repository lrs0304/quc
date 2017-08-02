#ifndef FRMGAUGESIMPLE_H
#define FRMGAUGESIMPLE_H

#include <QWidget>

namespace Ui {
class frmGaugeSimple;
}

class frmGaugeSimple : public QWidget
{
    Q_OBJECT

public:
    explicit frmGaugeSimple(QWidget *parent = 0);
    ~frmGaugeSimple();

private:
    Ui::frmGaugeSimple *ui;
};

#endif // FRMGAUGESIMPLE_H
