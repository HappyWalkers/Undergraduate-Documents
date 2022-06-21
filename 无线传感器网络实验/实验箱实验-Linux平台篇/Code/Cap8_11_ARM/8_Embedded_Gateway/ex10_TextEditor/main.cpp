#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow mainWin;
	mainWin.resize(320, 256);
	mainWin.move(50, 20);
    mainWin.show();
    return app.exec();
}
