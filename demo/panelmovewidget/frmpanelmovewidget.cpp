#include "frmpanelmovewidget.h"
#include "ui_frmpanelmovewidget.h"
#include "lightbutton.h"

frmPanelMoveWidget::frmPanelMoveWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::frmPanelMoveWidget)
{
	ui->setupUi(this);
	this->initForm();
}

frmPanelMoveWidget::~frmPanelMoveWidget()
{
	delete ui;
}

void frmPanelMoveWidget::initForm()
{
	QList<QColor> colors;
	colors.append(QColor(100, 184, 255));
	colors.append(QColor(255, 107, 107));
	colors.append(QColor(24, 189, 155));
	colors.append(QColor(1, 174, 103));
	colors.append(QColor(52, 73, 94));

	int x = 5;
	int y = 5;
	int radius = 50;

	for (int i = 0; i < 5; i++) {
		LightButton *btn = new LightButton(ui->frame);

		btn->setGeometry(x, y, radius, radius);
		x = x + radius;
		btn->setText(QString("0%10").arg(i + 1));
		btn->setCanMove(false);
		btn->setShowOverlay(false);
		btn->setBgColor(colors.at(i));
		btns.append(btn);
	}
}

void frmPanelMoveWidget::on_checkBox_stateChanged(int arg1)
{
	bool canMove = (arg1 != 0);

	foreach (LightButton *btn, btns) {
		btn->setCanMove(canMove);
	}
}

void frmPanelMoveWidget::on_btnShow_clicked()
{
	foreach (LightButton *btn, btns) {
		QString text = btn->getText();
		int x = btn->x();
		int y = btn->y();
		ui->textEdit->append(QString("名称:%1\tx:%2\ty:%3").arg(text).arg(x).arg(y));
	}
}

void frmPanelMoveWidget::on_btnClear_clicked()
{
	ui->textEdit->clear();
}
