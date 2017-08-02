#include "frmiconeditor.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    frmIconEditor w;
    w.show();

    return a.exec();
}
