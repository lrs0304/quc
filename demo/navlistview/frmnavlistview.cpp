#include "frmnavlistview.h"
#include "ui_frmnavlistview.h"
#include "qtimer.h"

frmNavListView::frmNavListView(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::frmNavListView)
{
	ui->setupUi(this);
	QTimer::singleShot(0, this, SLOT(initForm()));
}

frmNavListView::~frmNavListView()
{
	delete ui;
}

void frmNavListView::initForm()
{
	ui->listView1->readData(":/image/config.xml");
	ui->listView2->readData(":/image/config.xml");
	ui->listView3->readData(":/image/config.xml");
	ui->listView4->readData(":/image/config.xml");
}
