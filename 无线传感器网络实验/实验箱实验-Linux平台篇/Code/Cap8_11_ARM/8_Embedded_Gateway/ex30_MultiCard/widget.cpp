#include "widget.h"
#include "ui_widget.h"
#include <ChannelMan/RFIDChannelMan.h>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 选择900M读写器
    RFIDChannelMan::setChannel(RFIDChannelMan::ChannelUHF900M);
    // 创建900M读写器操作类对象
    rfid = new RLM100Control(this);
    // 连接必要的信号和槽
    connect(rfid, SIGNAL(newEPC(QByteArray)),
            this, SLOT(onEPCFound(QByteArray)));
    // 启动读写器
    rfid->start(RFIDChannelMan::getRfidPort());
}

Widget::~Widget()
{
    delete ui;
}

// 扫描到标签后显示在界面中
void Widget::onEPCFound(const QByteArray &uii)
{
    ui->epcLogText->append(uii.toHex());
}

// 启动多标签循环扫描操作
void Widget::on_multiLoopScanBtn_clicked()
{
    if(!rfid->startMultiScanLoop())
        ui->statusLabel->setText(tr("No card!"));
    else
        ui->statusLabel->setText(tr("multi scan card OK!"));
}

void Widget::on_stopBtn_clicked()
{
    rfid->stopOperation();
}

void Widget::on_clearResult_clicked()
{
    ui->epcLogText->clear();
}
