#include "widget.h"
#include "ui_widget.h"
#include <wifiWidget/wifi.h>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    Wifi::showOut();
}
