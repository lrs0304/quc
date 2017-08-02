#include "frmanimationbutton.h"
#include "ui_frmanimationbutton.h"

frmAnimationButton::frmAnimationButton(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmAnimationButton)
{
    ui->setupUi(this);
}

frmAnimationButton::~frmAnimationButton()
{
    delete ui;
}
