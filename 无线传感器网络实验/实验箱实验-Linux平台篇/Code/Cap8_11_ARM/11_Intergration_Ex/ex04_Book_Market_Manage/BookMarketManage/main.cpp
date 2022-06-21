#include <QtGui/QApplication>
#include "BookMarketManageWidget.h"
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BookMarketManageWidget w;

    if(qApp->desktop()->width() <= 800)
        w.showMaximized();
    else
        w.show();

    return a.exec();
}
