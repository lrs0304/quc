#ifndef FRMBARTEMP_H
#define FRMBARTEMP_H

#include <QWidget>

namespace Ui
{
class frmBarTemp;
}

class frmBarTemp : public QWidget
{
	Q_OBJECT

public:
	explicit frmBarTemp(QWidget *parent = 0);
	~frmBarTemp();

private:
	Ui::frmBarTemp *ui;

private slots:
	void initForm();
    void updateValue();
};

#endif // FRMBARTEMP_H
