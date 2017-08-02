#include "frmbattery.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    frmBattery w;
    w.show();

    return a.exec();
}
