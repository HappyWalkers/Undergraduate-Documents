#include "MainWidget.h"
#include "ui_MainWidget.h"
#include <QFile>
#include <QDebug>


#if 1
#define	DEFAULT_RFID_125K_PORT	"/dev/ttyUSB0"      //根据实际情况调整
#else
#define	DEFAULT_RFID_125K_PORT	"/dev/s3c2410_serial0"
#endif

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    int rtn;

    ui->setupUi(this);
    ui->lineEdit->setText(DBControl::server());
    qDebug()<<"is already in the Function start:"<<DBControl::server();


    // 选择125K读卡器
    RFIDChannelMan::setChannel(RFIDChannelMan::Channel125K);
    // 创建125K读卡器操作类对象
    rfid = new ID125KControl(this);
    // 连接扫描到卡的信号
    connect(rfid, SIGNAL(newCard(ulong,QByteArray)),
            this, SLOT(onNewCard(ulong,QByteArray)));
#ifdef _WIN32
    rtn = rfid->start("COM4");        //COM1 --->COM7
#else
    rtn = rfid->start(DEFAULT_RFID_125K_PORT);
//    bool  devFlag = 0;
//    bool  devFlag1 = 0;
//    devFlag = QFile("/sys/bus/usb-serial/devices/ttyUSB2").symLinkTarget().contains("1-1.1.4");

//    if(devFlag)
//        rfid->start(DEFAULT_RFID_COMM_DEV);
//    else
//    {
//        devFlag1 = QFile("/sys/bus/usb-serial/devices/ttyUSB1").symLinkTarget().contains("1-1.1.4");

//        if(devFlag1)
//          rfid->start(CHANGE_RFID_COMM_DEV_1);
//        else
//          rfid->start(CHANGE_RFID_COMM_DEV_0);
//    }
#endif
    qDebug()<<"[MainWidget] open COM return:"<<rtn;
    rtn = DBControl::CheckCreateTable();

    qDebug()<<"is already in the Function MainWidget! checkdatabase return:"<<rtn;
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

void MainWidget::on_reconnectBtn_clicked()
{
    if(!ui->lineEdit->text().isEmpty())
    {
        DBControl::setServer(ui->lineEdit->text());

    }
}
