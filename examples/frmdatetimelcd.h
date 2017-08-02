#ifndef FRMDATETIMELCD_H
#define FRMDATETIMELCD_H

#include <QWidget>

namespace Ui
{
class frmDateTimeLcd;
}

class frmDateTimeLcd : public QWidget
{
	Q_OBJECT

public:
	explicit frmDateTimeLcd(QWidget *parent = 0);
	~frmDateTimeLcd();

private:
	Ui::frmDateTimeLcd *ui;

private slots:
	void initForm();
};

#endif // FRMDATETIMELCD_H
