#include "frmgaugecar.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    frmGaugeCar w;
    w.show();

    return a.exec();
}
