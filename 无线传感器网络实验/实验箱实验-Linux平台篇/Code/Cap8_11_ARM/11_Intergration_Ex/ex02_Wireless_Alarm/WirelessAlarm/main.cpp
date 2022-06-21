#include <QtGui/QApplication>
#include "WirelessAlarmWidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WirelessAlarmWidget w;
    w.show();

    return a.exec();
}
