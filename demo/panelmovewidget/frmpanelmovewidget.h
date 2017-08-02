#ifndef FRMPANELMOVEWIDGET_H
#define FRMPANELMOVEWIDGET_H

#include <QWidget>

class LightButton;

namespace Ui
{
class frmPanelMoveWidget;
}

class frmPanelMoveWidget : public QWidget
{
	Q_OBJECT

public:
	explicit frmPanelMoveWidget(QWidget *parent = 0);
	~frmPanelMoveWidget();

private:
	Ui::frmPanelMoveWidget *ui;
	QList<LightButton *> btns;

private slots:
	void initForm();
	void on_checkBox_stateChanged(int arg1);
	void on_btnShow_clicked();
	void on_btnClear_clicked();
};

#endif // FRMPANELMOVEWIDGET_H
