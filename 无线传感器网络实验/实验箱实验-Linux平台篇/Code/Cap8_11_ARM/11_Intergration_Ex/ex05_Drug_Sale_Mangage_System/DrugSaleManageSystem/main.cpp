#include <QtGui/QApplication>
#include "DrugSaleManageSystemMainWidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DrugSaleManageSystemMainWidget w;
    w.show();

    return a.exec();
}
