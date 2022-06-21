#include <QApplication>

#include "MyWid.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MyWid screen;
    screen.setGeometry(100, 100, 200, 235);
    screen.show();
    return app.exec();
}

