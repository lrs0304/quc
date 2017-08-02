#include "frmadswidget.h"
#include "ui_frmadswidget.h"

frmAdsWidget::frmAdsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmAdsWidget)
{
    ui->setupUi(this);    
}

frmAdsWidget::~frmAdsWidget()
{
    delete ui;
}
