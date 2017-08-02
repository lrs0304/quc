#ifndef FRMGAUGEROUND_H
#define FRMGAUGEROUND_H

#include <QWidget>

namespace Ui {
class frmGaugeRound;
}

class frmGaugeRound : public QWidget
{
    Q_OBJECT

public:
    explicit frmGaugeRound(QWidget *parent = 0);
    ~frmGaugeRound();

private:
    Ui::frmGaugeRound *ui;
};

#endif // FRMGAUGEROUND_H
