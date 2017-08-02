#ifndef FRMBARSCALE_H
#define FRMBARSCALE_H

#include <QWidget>

namespace Ui
{
class frmBarScale;
}

class frmBarScale : public QWidget
{
	Q_OBJECT

public:
	explicit frmBarScale(QWidget *parent = 0);
	~frmBarScale();

private:
	Ui::frmBarScale *ui;

private slots:
	void initForm();
};

#endif // FRMBARSCALE_H
