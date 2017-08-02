#include "frmvumeter.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    frmVUMeter w;
    w.show();

    return a.exec();
}
