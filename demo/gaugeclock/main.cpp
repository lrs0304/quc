#include "frmgaugeclock.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    frmGaugeClock w;
    w.show();

    return a.exec();
}
