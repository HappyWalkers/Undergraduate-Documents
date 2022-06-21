#include "helloqt.h"
#include "ui_helloqt.h"

HelloQt::HelloQt(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HelloQt)
{
    ui->setupUi(this);
    QFont font;
    font.setPixelSize(18);
    //qDebug()<<font.pointSize();
    ui->label->setFont(font);
    //font.setPointSize();

}

HelloQt::~HelloQt()
{
    delete ui;
}
