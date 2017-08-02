#ifndef FRMBOTTOMWIDGET_H
#define FRMBOTTOMWIDGET_H

#include <QWidget>

namespace Ui
{
class frmBottomWidget;
}

class frmBottomWidget : public QWidget
{
	Q_OBJECT

public:
	explicit frmBottomWidget(QWidget *parent = 0);
	~frmBottomWidget();

private:
	Ui::frmBottomWidget *ui;
};

#endif // FRMBOTTOMWIDGET_H
