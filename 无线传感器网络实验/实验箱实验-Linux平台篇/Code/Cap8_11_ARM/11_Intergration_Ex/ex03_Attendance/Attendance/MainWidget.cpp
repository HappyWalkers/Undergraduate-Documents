#include "MainWidget.h"
#include "ui_MainWidget.h"
#include <QFile>
#include <QDebug>

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    DBControl::Create();
    ui->setupUi(this);

    // 选择125K读卡器
    RFIDChannelMan::setChannel(RFIDChannelMan::Channel125K);

    // 创建125K读卡器操作类对象
    rfid = new ID125KControl(this);
    // 连接扫描到卡的信号
    connect(rfid, SIGNAL(newCard(ulong,QByteArray)),
            this, SLOT(onNewCard(ulong,QByteArray)));
#ifdef _WIN32
    rfid->start("COM1");
#else
    bool  devFlag = 0;
    bool  devFlag1 = 0;
    devFlag = QFile("/sys/bus/usb-serial/devices/ttyUSB2").symLinkTarget().contains("1-1.1.4");

    if(devFlag)
        rfid->start(DEFAULT_RFID_COMM_DEV);        //("/dev/ttyUSB2");
    else
    {
        devFlag1 = QFile("/sys/bus/usb-serial/devices/ttyUSB1").symLinkTarget().contains("1-1.1.4");

        if(devFlag1)
          rfid->start(CHANGE_RFID_COMM_DEV_1);
        else
          rfid->start(CHANGE_RFID_COMM_DEV_0);
    }
#endif
}

MainWidget::~MainWidget()
{
    rfid->stop();
    rfid->deleteLater();
    DBControl::Destroy();
    delete ui;
}

void MainWidget::onNewCard(unsigned long decID, const QByteArray &byteID)
{
    if(decID == 0)
        return;

    switch(ui->tabWidget->currentIndex())
    {
    case 0:
        // ClockInWidget
        ui->clockInPage->onCardReaded(byteID.toHex());
        break;
    case 1:
        // ManageWidget
        ui->manPage->onCardReaded(byteID.toHex());
        break;
    }
}
