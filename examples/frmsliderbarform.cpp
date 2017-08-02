#include "frmsliderbarform.h"
#include "ui_frmsliderbarform.h"
#include "qtimer.h"
#include "qdebug.h"

frmSliderBarForm::frmSliderBarForm(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::frmSliderBarForm)
{
	ui->setupUi(this);
	this->initForm();
}

frmSliderBarForm::~frmSliderBarForm()
{
	delete ui;
}

void frmSliderBarForm::initForm()
{
	connect(ui->widget, SIGNAL(currentItemChanged(int, QString)), this, SLOT(currentItemChanged(int, QString)));
}

void frmSliderBarForm::currentItemChanged(int index, const QString &item)
{
	ui->stackedWidget->setCurrentIndex(index);
	qDebug() << "index" << index << "item" << item;
}
