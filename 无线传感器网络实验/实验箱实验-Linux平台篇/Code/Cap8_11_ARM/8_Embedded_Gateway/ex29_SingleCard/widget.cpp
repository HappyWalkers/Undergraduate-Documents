#include "widget.h"
#include "ui_widget.h"
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
    // 启动读写器
    rfid->start(RFIDChannelMan::getRfidPort());
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_singleScanBtn_clicked()
{
    QByteArray uii;
    if(!rfid->singleScan(uii))
        ui->statusLabel->setText(tr("No card!"));
    else
    {
        ui->statusLabel->setText(tr("scan card OK!"));
        ui->epcLogText->append(uii.toHex());
    }
}

void Widget::on_clearResult_clicked()
{
    ui->epcLogText->clear();
}
