#include "frmgaugespeed.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    frmGaugeSpeed w;
    w.show();

    return a.exec();
}
