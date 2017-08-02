#ifndef FRMWAVELINE_H
#define FRMWAVELINE_H

#include <QWidget>

namespace Ui
{
class frmWaveLine;
}

class frmWaveLine : public QWidget
{
	Q_OBJECT

public:
	explicit frmWaveLine(QWidget *parent = 0);
	~frmWaveLine();

private:
	Ui::frmWaveLine *ui;

private slots:
	void initForm();
	void updateValue();
};

#endif // FRMWAVELINE_H
