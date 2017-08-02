#ifndef FRMGAUGEWATCH_H
#define FRMGAUGEWATCH_H

#include <QWidget>

namespace Ui {
class frmGaugeWatch;
}

class frmGaugeWatch : public QWidget
{
    Q_OBJECT

public:
    explicit frmGaugeWatch(QWidget *parent = 0);
    ~frmGaugeWatch();

private:
    Ui::frmGaugeWatch *ui;
};

#endif // FRMGAUGEWATCH_H
