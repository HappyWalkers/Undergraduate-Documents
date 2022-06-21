#include <QtGui/QApplication>
#include "helloqt.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HelloQt w;
    w.show();

    return a.exec();
}
