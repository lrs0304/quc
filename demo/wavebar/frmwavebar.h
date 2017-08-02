#ifndef FRMWAVEBAR_H
#define FRMWAVEBAR_H

#include <QWidget>

namespace Ui
{
class frmWaveBar;
}

class frmWaveBar : public QWidget
{
	Q_OBJECT

public:
	explicit frmWaveBar(QWidget *parent = 0);
	~frmWaveBar();

protected:
	void resizeEvent(QResizeEvent *);

private:
	Ui::frmWaveBar *ui;

private slots:
    void initForm();
    void updateValue();
};

#endif // FRMWAVEBAR_H
