#ifndef FRMGAUGECAR_H
#define FRMGAUGECAR_H

#include <QWidget>

namespace Ui {
class frmGaugeCar;
}

class frmGaugeCar : public QWidget
{
    Q_OBJECT

public:
    explicit frmGaugeCar(QWidget *parent = 0);
    ~frmGaugeCar();

private:
    Ui::frmGaugeCar *ui;
};

#endif // FRMGAUGECAR_H
