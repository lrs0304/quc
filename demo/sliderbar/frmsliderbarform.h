#ifndef FRMSLIDERBARFORM_H
#define FRMSLIDERBARFORM_H

#include <QWidget>

namespace Ui
{
class frmSliderBarForm;
}

class frmSliderBarForm : public QWidget
{
	Q_OBJECT

public:
	explicit frmSliderBarForm(QWidget *parent = 0);
	~frmSliderBarForm();

private:
	Ui::frmSliderBarForm *ui;

private slots:
	void initForm();
    void currentItemChanged(int index, const QString &item);
};

#endif // FRMSLIDERBARFORM_H
