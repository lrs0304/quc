#include "frmgaugecompass.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    frmGaugeCompass w;
    w.show();

    return a.exec();
}
