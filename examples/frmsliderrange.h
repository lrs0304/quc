#ifndef FRMSLIDERRANGE_H
#define FRMSLIDERRANGE_H

#include <QWidget>

namespace Ui
{
class frmSliderRange;
}

class frmSliderRange : public QWidget
{
	Q_OBJECT

public:
	explicit frmSliderRange(QWidget *parent = 0);
	~frmSliderRange();

private:
	Ui::frmSliderRange *ui;
};

#endif // FRMSLIDERRANGE_H
