#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 选择扫描枪
    RFIDChannelMan::setChannel(RFIDChannelMan::ChannelScanGun);
    // 创建扫描枪操作类对象
    scanGun = new ScanGunControl(this);
    // 连接必要的信号
    connect(scanGun, SIGNAL(scanResult(QByteArray)),
            this, SLOT(onScanResult(QByteArray)));
    scanGun->start(RFIDChannelMan::getRfidPort());
}

Widget::~Widget()
{
    delete ui;
}

void Widget::onScanResult(const QByteArray &result)
{
    ui->resultEdit->setText(result);
}

void Widget::on_clearBtn_clicked()
{
    ui->resultEdit->clear();
}
