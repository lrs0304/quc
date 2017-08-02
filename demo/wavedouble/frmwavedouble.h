#ifndef FRMWAVEDOUBLE_H
#define FRMWAVEDOUBLE_H

#include <QWidget>

namespace Ui
{
class frmWaveDouble;
}

class frmWaveDouble : public QWidget
{
	Q_OBJECT

public:
	explicit frmWaveDouble(QWidget *parent = 0);
	~frmWaveDouble();

private:
	Ui::frmWaveDouble *ui;

private slots:
	void initForm();
	void updateValue();
};

#endif // FRMWAVEDOUBLE_H
