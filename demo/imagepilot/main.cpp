#include "frmimagepilot.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    frmImagePilot w;
    w.show();

    return a.exec();
}
