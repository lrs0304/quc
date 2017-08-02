#ifndef FRMPROGRESSBARWAIT_H
#define FRMPROGRESSBARWAIT_H

#include <QWidget>

namespace Ui
{
class frmProgressBarWait;
}

class frmProgressBarWait : public QWidget
{
	Q_OBJECT

public:
    explicit frmProgressBarWait(QWidget *parent = 0);
    ~frmProgressBarWait();

private:
    Ui::frmProgressBarWait *ui;
};

#endif // frmProgressBarWait_H
