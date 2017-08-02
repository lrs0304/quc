#ifndef FRMVERIFIEDCODE_H
#define FRMVERIFIEDCODE_H

#include <QWidget>

namespace Ui {
class frmVerifiedCode;
}

class frmVerifiedCode : public QWidget
{
    Q_OBJECT

public:
    explicit frmVerifiedCode(QWidget *parent = 0);
    ~frmVerifiedCode();

private slots:
    void on_btnReflash_clicked();

    void on_btnCheck_clicked();

private:
    Ui::frmVerifiedCode *ui;
};

#endif // FRMVERIFIEDCODE_H
