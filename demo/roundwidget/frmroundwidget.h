#ifndef FRMROUNDWIDGET_H
#define FRMROUNDWIDGET_H

#include <QWidget>

namespace Ui
{
class frmRoundWidget;
}

class frmRoundWidget : public QWidget
{
	Q_OBJECT

public:
	explicit frmRoundWidget(QWidget *parent = 0);
	~frmRoundWidget();

private:
	Ui::frmRoundWidget *ui;
};

#endif // FRMROUNDWIDGET_H
