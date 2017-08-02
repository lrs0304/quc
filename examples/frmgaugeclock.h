#ifndef FRMGAUGECLOCK_H
#define FRMGAUGECLOCK_H

#include <QWidget>

namespace Ui {
class frmGaugeClock;
}

class frmGaugeClock : public QWidget
{
    Q_OBJECT

public:
    explicit frmGaugeClock(QWidget *parent = 0);
    ~frmGaugeClock();

private:
    Ui::frmGaugeClock *ui;
};

#endif // FRMGAUGECLOCK_H
