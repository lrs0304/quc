#ifndef FRMLEDTEXT_H
#define FRMLEDTEXT_H

#include <QWidget>

namespace Ui
{
class frmLedText;
}

class frmLedText : public QWidget
{
	Q_OBJECT

public:
    explicit frmLedText(QWidget *parent = 0);
    ~frmLedText();

private:
    Ui::frmLedText *ui;
};

#endif // FRMLEDTEXT_H
