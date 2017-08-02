#ifndef FRMSLIDERRULER_H
#define FRMSLIDERRULER_H

#include <QWidget>

namespace Ui
{
class frmSliderRuler;
}

class frmSliderRuler : public QWidget
{
	Q_OBJECT

public:
	explicit frmSliderRuler(QWidget *parent = 0);
	~frmSliderRuler();

private:
	Ui::frmSliderRuler *ui;
};

#endif // FRMSLIDERRULER_H
