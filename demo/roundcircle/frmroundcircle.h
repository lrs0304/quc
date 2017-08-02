#ifndef FRMROUNDCIRCLE_H
#define FRMROUNDCIRCLE_H

#include <QWidget>

namespace Ui
{
class frmRoundCircle;
}

class frmRoundCircle : public QWidget
{
	Q_OBJECT

public:
	explicit frmRoundCircle(QWidget *parent = 0);
	~frmRoundCircle();

private:
	Ui::frmRoundCircle *ui;
};

#endif // FRMROUNDCIRCLE_H
