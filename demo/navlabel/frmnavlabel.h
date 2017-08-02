#ifndef FRMNAVLABEL_H
#define FRMNAVLABEL_H

#include <QWidget>

namespace Ui
{
class frmNavLabel;
}

class frmNavLabel : public QWidget
{
	Q_OBJECT

public:
	explicit frmNavLabel(QWidget *parent = 0);
	~frmNavLabel();

private:
	Ui::frmNavLabel *ui;
};

#endif // FRMNAVLABEL_H
