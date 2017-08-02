#ifndef FRMVUMETER_H
#define FRMVUMETER_H

#include <QWidget>

namespace Ui {
class frmVUMeter;
}

class frmVUMeter : public QWidget
{
    Q_OBJECT

public:
    explicit frmVUMeter(QWidget *parent = 0);
    ~frmVUMeter();

private:
    Ui::frmVUMeter *ui;
};

#endif // FRMVUMETER_H
