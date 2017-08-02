#ifndef FRMSLIDERBAR_H
#define FRMSLIDERBAR_H

#include <QWidget>

class SliderBar;

namespace Ui
{
class frmSliderBar;
}

class frmSliderBar : public QWidget
{
	Q_OBJECT

public:
	explicit frmSliderBar(QWidget *parent = 0);
	~frmSliderBar();

private:
	Ui::frmSliderBar *ui;

private slots:
	void initForm();
    void setIndex();
};

#endif // FRMSLIDERBAR_H
