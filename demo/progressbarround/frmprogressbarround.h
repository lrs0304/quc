#ifndef FRMPROGRESSBARROUND_H
#define FRMPROGRESSBARROUND_H

#include <QWidget>

class ProgressBarRound;

namespace Ui
{
class frmProgressBarRound;
}

class frmProgressBarRound : public QWidget
{
	Q_OBJECT

public:
	explicit frmProgressBarRound(QWidget *parent = 0);
	~frmProgressBarRound();

private:
	Ui::frmProgressBarRound *ui;

private slots:
	void connectToSlider(ProgressBarRound *bar);
};

#endif // FRMPROGRESSBARROUND_H
