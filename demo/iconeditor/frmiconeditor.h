#ifndef FRMICONEDITOR_H
#define FRMICONEDITOR_H

#include <QWidget>

namespace Ui {
class frmIconEditor;
}

class frmIconEditor : public QWidget
{
    Q_OBJECT

public:
    explicit frmIconEditor(QWidget *parent = 0);
    ~frmIconEditor();

private:
    Ui::frmIconEditor *ui;

private slots:
    void initForm();
    void on_btnOpen_clicked();
    void on_btnSave_clicked();
    void on_btnSaveBg_clicked();
    void on_cboxZoom_activated(const QString &arg1);
};

#endif // FRMICONEDITOR_H
