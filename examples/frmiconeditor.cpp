#include "frmiconeditor.h"
#include "ui_frmiconeditor.h"
#include "qfiledialog.h"

frmIconEditor::frmIconEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmIconEditor)
{
    ui->setupUi(this);
    this->initForm();
}

frmIconEditor::~frmIconEditor()
{
    delete ui;
}

void frmIconEditor::initForm()
{
    for (int i = 3; i < 50; i++) {
        ui->cboxZoom->addItem(QString::number(i));
    }

    ui->cboxZoom->setCurrentIndex(5);
}

void frmIconEditor::on_btnOpen_clicked()
{
    QString file = QFileDialog::getOpenFileName(this, "打开");
    if (!file.isEmpty()) {
        ui->widget->setIconImage(file);
    }
}

void frmIconEditor::on_btnSave_clicked()
{
    QString file = QFileDialog::getSaveFileName(this, "保存");
    if (!file.isEmpty()) {
        ui->widget->saveIcon(file);
    }
}

void frmIconEditor::on_btnSaveBg_clicked()
{
    QString file = QFileDialog::getSaveFileName(this, "保存");
    if (!file.isEmpty()) {
        ui->widget->saveBg(file);
    }
}

void frmIconEditor::on_cboxZoom_activated(const QString &arg1)
{
    ui->widget->setZoomFactor(arg1.toInt());
}
