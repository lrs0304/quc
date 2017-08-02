#include "frmimageview.h"
#include "ui_frmimageview.h"
#include "qfiledialog.h"

frmImageView::frmImageView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmImageView)
{
    ui->setupUi(this);
}

frmImageView::~frmImageView()
{
    delete ui;
}

void frmImageView::on_btnOpen_clicked()
{
    QString path = QFileDialog::getExistingDirectory(this, "选择文件夹");

    if (!path.isEmpty()) {
        ui->labPath->setText(path);
        ui->imageView->load(path);
    }
}

void frmImageView::on_ckFill_stateChanged(int arg1)
{
    ui->imageView->setFill(arg1 != 0);
}

void frmImageView::on_ckFade_stateChanged(int arg1)
{
    ui->imageView->setFade(arg1 != 0);
}

void frmImageView::on_ckKeyMove_stateChanged(int arg1)
{
    ui->imageView->setKeyMove(arg1 != 0);
}
