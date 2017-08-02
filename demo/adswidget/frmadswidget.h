#ifndef FRMADSWIDGET_H
#define FRMADSWIDGET_H

#include <QWidget>

namespace Ui {
class frmAdsWidget;
}

class frmAdsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit frmAdsWidget(QWidget *parent = 0);
    ~frmAdsWidget();

private:
    Ui::frmAdsWidget *ui;
};

#endif // FRMADSWIDGET_H
