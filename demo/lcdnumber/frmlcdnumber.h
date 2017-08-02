#ifndef FRMLCDNUMBER_H
#define FRMLCDNUMBER_H

#include <QWidget>

namespace Ui
{
class frmLcdNumber;
}

class frmLcdNumber : public QWidget
{
	Q_OBJECT

public:
	explicit frmLcdNumber(QWidget *parent = 0);
	~frmLcdNumber();

private:
	Ui::frmLcdNumber *ui;

private slots:
	void initForm();
    void updateValue();
};

#endif // FRMLCDNUMBER_H
