#ifndef FRMTUMBLER_H
#define FRMTUMBLER_H

#include <QWidget>

namespace Ui
{
class frmTumbler;
}

class frmTumbler : public QWidget
{
	Q_OBJECT

public:
	explicit frmTumbler(QWidget *parent = 0);
	~frmTumbler();

private:
	Ui::frmTumbler *ui;

private slots:
	void initForm();
};

#endif // FRMTUMBLER_H
