#include <QtGui/QApplication>
#include <QWSServer>
#include "widget.h"
#define MAIN_NODE_CONFIG
#include <node_config.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    if(QApplication::GuiServer == a.type())
    {
    	QImage img = QImage("/root/applogo.png");
    	QBrush brush = QBrush(img);
//    	QWSServer::setBackground(brush);
    }
    Widget w("127.0.0.1");
    w.showMaximized();

    return a.exec();
}
