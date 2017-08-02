#ifndef FRMLINERULER_H
#define FRMLINERULER_H

#include <QWidget>

namespace Ui
{
class frmLineRuler;
}

class frmLineRuler : public QWidget
{
	Q_OBJECT

public:
	explicit frmLineRuler(QWidget *parent = 0);
	~frmLineRuler();

private:
	Ui::frmLineRuler *ui;
};

#endif // FRMLINERULER_H
