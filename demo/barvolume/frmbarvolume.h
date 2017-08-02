#ifndef FRMBARVOLUME_H
#define FRMBARVOLUME_H

#include <QWidget>

namespace Ui
{
class frmBarVolume;
}

class frmBarVolume : public QWidget
{
	Q_OBJECT

public:
	explicit frmBarVolume(QWidget *parent = 0);
	~frmBarVolume();

private:
	Ui::frmBarVolume *ui;

private slots:
	void initForm();
    void updateValue();
};

#endif // FRMBARVOLUME_H
