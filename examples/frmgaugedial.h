#ifndef FRMGAUGEDIAL_H
#define FRMGAUGEDIAL_H

#include <QWidget>

namespace Ui {
class frmGaugeDial;
}

class frmGaugeDial : public QWidget
{
    Q_OBJECT

public:
    explicit frmGaugeDial(QWidget *parent = 0);
    ~frmGaugeDial();

private:
    Ui::frmGaugeDial *ui;
};

#endif // FRMGAUGEDIAL_H
