#include "frmverifiedcode.h"
#include "ui_frmverifiedcode.h"

frmVerifiedCode::frmVerifiedCode(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmVerifiedCode)
{
    ui->setupUi(this);
}

frmVerifiedCode::~frmVerifiedCode()
{
    delete ui;
}

void frmVerifiedCode::on_btnReflash_clicked()
{
    ui->verifiedCode->loadCode();
}

void frmVerifiedCode::on_btnCheck_clicked()
{
    QString str = ui->lineEdit->text();
    if (str == ui->verifiedCode->getCode()) {
        ui->label->setText("校验结果: 成功");
    } else {
        ui->label->setText("校验结果: 失败");
    }
}
