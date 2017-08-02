#ifndef FRMTEXTMOVEWIDGET_H
#define FRMTEXTMOVEWIDGET_H

#include <QWidget>

namespace Ui
{
class frmTextMoveWidget;
}

class frmTextMoveWidget : public QWidget
{
	Q_OBJECT

public:
	explicit frmTextMoveWidget(QWidget *parent = 0);
	~frmTextMoveWidget();

private:
	Ui::frmTextMoveWidget *ui;
};

#endif // FRMTEXTMOVEWIDGET_H
