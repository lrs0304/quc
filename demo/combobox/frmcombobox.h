#ifndef FRMCOMBOBOX_H
#define FRMCOMBOBOX_H

#include <QWidget>

namespace Ui {
class frmComboBox;
}

class frmComboBox : public QWidget
{
    Q_OBJECT

public:
    explicit frmComboBox(QWidget *parent = 0);
    ~frmComboBox();

private:
    Ui::frmComboBox *ui;
};

#endif // FRMCOMBOBOX_H
