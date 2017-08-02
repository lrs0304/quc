#include "frmwavebar.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    frmWaveBar w;
    w.show();

    return a.exec();
}
