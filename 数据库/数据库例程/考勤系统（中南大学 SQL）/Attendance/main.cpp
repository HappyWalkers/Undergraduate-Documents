#include <QtGui/QApplication>
#include "MainWidget.h"
#include "DBControl.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DBControl::instance();
    qDebug()<<"====is already in the Function main!";

    MainWidget w;

    w.showFullScreen();
    //w.show();

    return a.exec();
}
