#include "Widget.h"
#include "ui_Widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 选择2.4G读卡器
    RFIDChannelMan::setChannel(RFIDChannelMan::ChannelMicrowave);
    // 创建2.4G读卡器操作类对象
    rfid = new MicroWaveControl(this);
    // 连接必要的信号
    connect(rfid, SIGNAL(newCard(int,int,bool,ulong,QByteArray)),
            this, SLOT(onRfidNewCard(int,int,bool,ulong,QByteArray)));
    rfid->start(RFIDChannelMan::getRfidPort());
}

Widget::~Widget()
{
    delete ui;
}

void Widget::onRfidNewCard(int readerAddr, int cardType, bool lowPower, unsigned long decID, const QByteArray &byteID)
{
    // 将卡号转换为字符串
    QString info = QString::number(decID);
    // 如果标签欠压，则增加欠压的提示
    if(lowPower)
        info += " LowPower";

    // 将提示信息显示在文本框内
    ui->plainTextEdit->appendPlainText(info);
}

void Widget::on_clearBtn_clicked()
{
    ui->plainTextEdit->clear();
}
