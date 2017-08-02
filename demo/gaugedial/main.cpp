#include "frmgaugedial.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    frmGaugeDial w;
    w.show();

    return a.exec();
}
