#ifndef FRMGAUGEARC_H
#define FRMGAUGEARC_H

#include <QWidget>

namespace Ui {
class frmGaugeArc;
}

class frmGaugeArc : public QWidget
{
    Q_OBJECT

public:
    explicit frmGaugeArc(QWidget *parent = 0);
    ~frmGaugeArc();

private:
    Ui::frmGaugeArc *ui;
};

#endif // FRMGAUGEARC_H
