#include "widget.h"
#include "ui_widget.h"
#include "blehall.h"

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
    BleHall::showOut("127.0.0.1", 0xFF);
}
