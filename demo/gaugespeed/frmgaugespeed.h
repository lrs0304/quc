#ifndef FRMGAUGESPEED_H
#define FRMGAUGESPEED_H

#include <QWidget>

namespace Ui {
class frmGaugeSpeed;
}

class frmGaugeSpeed : public QWidget
{
    Q_OBJECT

public:
    explicit frmGaugeSpeed(QWidget *parent = 0);
    ~frmGaugeSpeed();

private:
    Ui::frmGaugeSpeed *ui;
};

#endif // FRMGAUGESPEED_H
