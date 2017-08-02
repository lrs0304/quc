#include "frmwaveplot.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    frmWavePlot w;
    w.show();

    return a.exec();
}
