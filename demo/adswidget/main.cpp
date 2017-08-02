#include "frmadswidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    frmAdsWidget w;
    w.show();

    return a.exec();
}
