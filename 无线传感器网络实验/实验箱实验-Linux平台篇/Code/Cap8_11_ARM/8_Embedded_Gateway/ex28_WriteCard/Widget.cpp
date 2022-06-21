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
    // 连接出错、寻卡成功以及读卡成功的信号
    connect(rfid, SIGNAL(error(int,QString)),
            this, SLOT(onRfidError(int,QString)));
    connect(rfid, SIGNAL(foundCard(QByteArray)),
            this, SLOT(onRfidFoundCard(QByteArray)));
    connect(rfid, SIGNAL(dataReaded(int,QByteArray)),
            this, SLOT(onRfidDataReaded(int,QByteArray)));
    connect(rfid, SIGNAL(dataWritten(int)),
            this, SLOT(onRfidDataWritten(int)));
    rfid->start(RFIDChannelMan::getRfidPort());
}

Widget::~Widget()
{
    delete ui;
}

void Widget::onRfidError(int cmdType, const QString &result)
{
    // 读卡未成功，继续读卡操作
    if(cmdType == IEEE14443Control::ReadCard)
        rfid->readCard(ui->spinBox->value());
    // 写卡未成功，显示提示信息
    else if(cmdType == IEEE14443Control::WriteCard)
        ui->statusLabel->setText("Write Failed");
}

void Widget::onRfidFoundCard(const QByteArray &cardid)
{
    // 读卡过程中获得卡号，显示卡号
    ui->lineEdit->setText(cardid.toHex());
}

void Widget::onRfidDataReaded(int block, const QByteArray &data)
{
    // 读卡完成，显示读取到到数据
    ui->lineEdit_2->setText(data.toHex());
}

void Widget::on_pushButton_clicked()
{
    rfid->readCard(ui->spinBox->value());
}

void Widget::onRfidDataWritten(int block)
{
    // 写卡完成，显示提示信息
    ui->statusLabel->setText("Data Written!");
}

void Widget::on_pushButton_2_clicked()
{
    // 获得文本框内的数据并转换为字节数组然后启动写卡操作
    QByteArray data = QByteArray::fromHex(
            ui->lineEdit_2->text().toLatin1());
    if(!rfid->writeCard(ui->spinBox->value(), data))
        ui->statusLabel->setText("Failed to start write");
}
