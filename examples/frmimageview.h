#ifndef FRMIMAGEVIEW_H
#define FRMIMAGEVIEW_H

#include <QWidget>

namespace Ui
{
class frmImageView;
}

class frmImageView : public QWidget
{
	Q_OBJECT

public:
	explicit frmImageView(QWidget *parent = 0);
	~frmImageView();

private:
	Ui::frmImageView *ui;

private slots:
	void on_btnOpen_clicked();
	void on_ckFill_stateChanged(int arg1);
	void on_ckFade_stateChanged(int arg1);
	void on_ckKeyMove_stateChanged(int arg1);
};

#endif // FRMIMAGEVIEW_H
