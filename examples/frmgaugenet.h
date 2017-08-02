#ifndef FRMGAUGENET_H
#define FRMGAUGENET_H

#include <QWidget>

namespace Ui {
class frmGaugeNet;
}

class frmGaugeNet : public QWidget
{
    Q_OBJECT

public:
    explicit frmGaugeNet(QWidget *parent = 0);
    ~frmGaugeNet();

private:
    Ui::frmGaugeNet *ui;
};

#endif // FRMGAUGENET_H
