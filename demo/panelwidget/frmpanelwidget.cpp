#include "frmpanelwidget.h"
#include "ui_frmpanelwidget.h"
#include "qpushbutton.h"
#include "frmpanelwidgetx.h"

frmPanelWidget::frmPanelWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::frmPanelWidget)
{
	ui->setupUi(this);
	this->initForm();
}

frmPanelWidget::~frmPanelWidget()
{
	delete ui;
}

void frmPanelWidget::initForm()
{
	QList<QWidget *> widgets1;
	int columnCount1 = 10;

	for (int i = 1; i <= 100; i++) {
		QPushButton *btn = new QPushButton;
		btn->setText(QString::number(i));
		btn->setFixedHeight(100);
		btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
		widgets1.append(btn);
	}

	ui->widget1->setWidget(widgets1, columnCount1);
    ui->widget1->setMargin(3);

	QList<QWidget *> widgets2;
    int columnCount2 = 6;

    for (int i = 1; i <= 50; i++) {
		frmPanelWidgetX *frm = new frmPanelWidgetX;
        frm->setFixedHeight(105);
        frm->setMinimumWidth(220);
		frm->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
		widgets2.append(frm);
	}

	ui->widget2->setWidget(widgets2, columnCount2);
    ui->widget2->setMargin(3);
}
