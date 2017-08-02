#ifndef FRMNAVPROGRESSBAR_H
#define FRMNAVPROGRESSBAR_H

#include <QWidget>

namespace Ui
{
class frmNavProgressBar;
}

class frmNavProgressBar : public QWidget
{
	Q_OBJECT

public:
	explicit frmNavProgressBar(QWidget *parent = 0);
	~frmNavProgressBar();

private:
	Ui::frmNavProgressBar *ui;

private slots:
	void initForm();
};

#endif // FRMNAVPROGRESSBAR_H
