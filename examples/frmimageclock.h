#ifndef FRMIMAGECLOCK_H
#define FRMIMAGECLOCK_H

#include <QWidget>

namespace Ui {
class frmImageClock;
}

class frmImageClock : public QWidget
{
    Q_OBJECT

public:
    explicit frmImageClock(QWidget *parent = 0);
    ~frmImageClock();

private:
    Ui::frmImageClock *ui;
};

#endif // FRMIMAGECLOCK_H
