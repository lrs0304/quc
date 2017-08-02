#include "frmgaugesimple.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    frmGaugeSimple w;
    w.show();

    return a.exec();
}
