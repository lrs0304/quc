#ifndef FRMGAUGEPROGRESSBAR_H
#define FRMGAUGEPROGRESSBAR_H

#include <QWidget>

namespace Ui {
class frmGaugeProgressBar;
}

class frmGaugeProgressBar : public QWidget
{
    Q_OBJECT

public:
    explicit frmGaugeProgressBar(QWidget *parent = 0);
    ~frmGaugeProgressBar();

private:
    Ui::frmGaugeProgressBar *ui;
};

#endif // FRMGAUGEPROGRESSBAR_H
