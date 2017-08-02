#ifndef FRMGAUGECOMPASS_H
#define FRMGAUGECOMPASS_H

#include <QWidget>

namespace Ui {
class frmGaugeCompass;
}

class frmGaugeCompass : public QWidget
{
    Q_OBJECT

public:
    explicit frmGaugeCompass(QWidget *parent = 0);
    ~frmGaugeCompass();

private:
    Ui::frmGaugeCompass *ui;
};

#endif // FRMGAUGECOMPASS_H
