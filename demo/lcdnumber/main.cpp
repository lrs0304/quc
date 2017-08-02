#include "frmlcdnumber.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    frmLcdNumber w;
    w.show();

    return a.exec();
}
