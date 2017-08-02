#include "frmtumbler.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    frmTumbler w;
    w.show();

    return a.exec();
}
