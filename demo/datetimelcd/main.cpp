#include "frmdatetimelcd.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    frmDateTimeLcd w;
    w.show();

    return a.exec();
}
