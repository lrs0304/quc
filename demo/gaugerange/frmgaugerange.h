#ifndef FRMGAUGERANGE_H
#define FRMGAUGERANGE_H

#include <QWidget>

namespace Ui {
class frmGaugeRange;
}

class frmGaugeRange : public QWidget
{
    Q_OBJECT

public:
    explicit frmGaugeRange(QWidget *parent = 0);
    ~frmGaugeRange();

private:
    Ui::frmGaugeRange *ui;
};

#endif // FRMGAUGERANGE_H
