#include "Widget.h"
#include "ui_Widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    // 选择125K读卡器
    RFIDChannelMan::setChannel(RFIDChannelMan::Channel125K);

    // 创建125K读卡器操作类对象
    rfid = new ID125KControl(this);
    // 连接扫描到卡的信号
    connect(rfid, SIGNAL(newCard(ulong,QByteArray)),
            this, SLOT(onNewCard(ulong,QByteArray)));

    rfid->start(RFIDChannelMan::getRfidPort());
}

Widget::~Widget()
{
    delete ui;
}

void Widget::onNewCard(unsigned long decID, const QByteArray &byteID)
{
    ui->cardIDList->appendPlainText(QString::number(decID));
}

void Widget::on_clearBtn_clicked()
{
    ui->cardIDList->clear();
}
