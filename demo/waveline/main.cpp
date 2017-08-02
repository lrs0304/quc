#include "frmwaveline.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    frmWaveLine w;
    w.show();

    return a.exec();
}
