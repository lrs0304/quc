#include "frmpanelwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    frmPanelWidget w;
    w.show();

    return a.exec();
}
