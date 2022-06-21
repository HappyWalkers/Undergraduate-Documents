#include <QtGui/QApplication>
#include "IntelligentMedicalWidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    IntelligentMedicalWidget w;
    w.show();

    return a.exec();
}
