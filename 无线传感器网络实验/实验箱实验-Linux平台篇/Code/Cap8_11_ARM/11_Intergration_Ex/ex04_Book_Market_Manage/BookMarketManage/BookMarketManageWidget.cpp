#include "BookMarketManageWidget.h"
#include "ui_BookMarketManageWidget.h"
#include <ChannelMan/RFIDChannelMan.h>
#include "DBControl.h"
#include <QMessageBox>
#include <QFile>
#include <QDebug>

BookMarketManageWidget::BookMarketManageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BookMarketManageWidget),
    rfid(NULL)
{
    DBControl::Create();
    this->trans = new QTranslator(this);
    this->trans->load(":/zh_CN.qm");
    qApp->installTranslator(this->trans);
    ui->setupUi(this);

    loadUartDev();

    rfid = new RLM100Control(this);
    connect(rfid, SIGNAL(newEPC(QByteArray)),
            this, SLOT(onEPCFound(QByteArray)));

    on_openCloseBtn_clicked(false);
}

BookMarketManageWidget::~BookMarketManageWidget()
{
    DBControl::Destroy();
    delete ui;
}

void BookMarketManageWidget::loadUartDev()
{
#ifdef _WIN32
    commPortName = "COM1";
#else
    bool  devFlag = 0;
    bool  devFlag1 = 0;

    devFlag = QFile("/sys/bus/usb-serial/devices/ttyUSB2").symLinkTarget().contains("1-1.1.4");

    if(devFlag)
        commPortName = DEFAULT_RFID_COMM_DEV;        //("/dev/ttyUSB2");
    else
    {
        devFlag1 = QFile("/sys/bus/usb-serial/devices/ttyUSB1").symLinkTarget().contains("1-1.1.4");

        if(devFlag1)
          commPortName = CHANGE_RFID_COMM_DEV_1;
        else
          commPortName = CHANGE_RFID_COMM_DEV_0;
    }
#endif
}

void BookMarketManageWidget::onTimeout()
{
    on_openCloseBtn_clicked(false);
    QMessageBox::warning(this, tr("Warning"),
                         tr("Comm error, Please check the H/W Connection!"));
}

void BookMarketManageWidget::onEPCFound(const QByteArray &uii)
{
    qDebug()<<"uii ="<<uii.toHex();
    switch(ui->opList->currentRow())
    {
    case 0:
        // borrow
        ui->borrowPage->onCardDetected(uii.toHex());
        break;
    case 1:
        // back
        ui->backPage->onCardDetected(uii.toHex());
        break;
    case 2:
        // manage
        ui->managePage->onCardDetected(uii.toHex());
        break;
    }
}

void BookMarketManageWidget::on_openCloseBtn_clicked(bool checked)
{
    if(!rfid->isActive())
    {
        //qDebug()<<"set mode success";
        RFIDChannelMan::setChannel(RFIDChannelMan::ChannelUHF900M);
        rfid->start(commPortName);
        rfid->stopOperation();
        ui->openCloseBtn->setText(tr("Opened"));
        ui->openCloseBtn->setIcon(QIcon(":/pic/shut_down_normal.png"));
        ui->contentWidget->setEnabled(true);
        rfid->startSingleScanLoop();
    }
    else
    {
        rfid->stopOperation();
        rfid->stop();
        ui->openCloseBtn->setText(tr("Closed"));
        ui->openCloseBtn->setIcon(QIcon(":/pic/shut_down_grayed.png"));
        ui->contentWidget->setEnabled(false);
    }
    ui->openCloseBtn->setChecked(rfid->isActive());
}
