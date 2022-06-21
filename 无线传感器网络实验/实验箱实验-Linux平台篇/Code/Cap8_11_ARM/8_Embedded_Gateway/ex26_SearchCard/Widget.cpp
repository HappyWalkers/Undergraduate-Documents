#include "Widget.h"
#include "ui_Widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 选择13.56M读写器
    RFIDChannelMan::setChannel(RFIDChannelMan::ChannelIEEE14443);
    // 创建13.56M读写器操作类对象
    rfid = new IEEE14443Control(this);
    // 连接出错和寻卡成功的信号
    connect(rfid, SIGNAL(error(int,QString)),
            this, SLOT(onRfidError(int,QString)));
    connect(rfid, SIGNAL(foundCard(QByteArray)),
            this, SLOT(onRfidFoundCard(QByteArray)));
    rfid->start(RFIDChannelMan::getRfidPort());
}

Widget::~Widget()
{
    delete ui;
}

void Widget::onRfidError(int cmdType, const QString &result)
{
    // 寻卡未成功，继续寻卡操作
    if(cmdType == IEEE14443Control::GetCardId)
        rfid->getCardId();
}

void Widget::onRfidFoundCard(const QByteArray &cardid)
{
    // 寻卡成功，显示卡号，不再启动寻卡操作
    ui->lineEdit->setText(cardid.toHex());
}

void Widget::on_pushButton_clicked()
{
    // 点击按钮时，启动寻卡操作
    rfid->getCardId();
}
