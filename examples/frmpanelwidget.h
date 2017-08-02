#ifndef FRMPANELWIDGET_H
#define FRMPANELWIDGET_H

#include <QWidget>

namespace Ui
{
class frmPanelWidget;
}

class frmPanelWidget : public QWidget
{
	Q_OBJECT

public:
	explicit frmPanelWidget(QWidget *parent = 0);
	~frmPanelWidget();

private:
	Ui::frmPanelWidget *ui;

private slots:
	void initForm();
};

#endif // FRMPANELWIDGET_H
