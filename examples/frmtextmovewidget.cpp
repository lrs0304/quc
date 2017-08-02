#include "frmtextmovewidget.h"
#include "ui_frmtextmovewidget.h"

frmTextMoveWidget::frmTextMoveWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::frmTextMoveWidget)
{
	ui->setupUi(this);	
}

frmTextMoveWidget::~frmTextMoveWidget()
{
	delete ui;
}
