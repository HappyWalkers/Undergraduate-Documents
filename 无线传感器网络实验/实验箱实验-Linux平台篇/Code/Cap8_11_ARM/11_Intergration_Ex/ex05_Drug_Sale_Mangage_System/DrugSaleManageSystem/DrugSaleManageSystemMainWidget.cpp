#include "DrugSaleManageSystemMainWidget.h"
#include "ui_DrugSaleManageSystemMainWidget.h"
#include <ChannelMan/RFIDChannelMan.h>
#include "DBControl.h"
#include <QMessageBox>
#include <QFile>
#include <QDebug>

DrugSaleManageSystemMainWidget::DrugSaleManageSystemMainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DrugSaleManageSystemMainWidget)
{
    DBControl::Create();
    trans = new QTranslator(this);
    trans->load(":/zh_CN.qm");
    qApp->installTranslator(trans);
    ui->setupUi(this);

    loadUartDev();

    rfid = new RLM100Control(this);
    connect(rfid, SIGNAL(newEPC(QByteArray)),
            this, SLOT(onEPCFound(QByteArray)));

    on_openCloseBtn_clicked(false);
}

DrugSaleManageSystemMainWidget::~DrugSaleManageSystemMainWidget()
{
    DBControl::Destroy();
    delete ui;
}

void DrugSaleManageSystemMainWidget::loadUartDev()
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

void DrugSaleManageSystemMainWidget::onTimeout()
{
    on_openCloseBtn_clicked(false);
    QMessageBox::warning(this, tr("Warning"),
                         tr("Comm error, Please check the H/W Connection!"));
}

void DrugSaleManageSystemMainWidget::onEPCFound(const QByteArray &uii)
{
    qDebug()<<"uii ="<<uii.toHex();
    switch(ui->opListTable->currentIndex())
    {
    case 0:
        // sale
        ui->saleOutPage->onCardDetected(uii.toHex());
        break;
    case 1:
        // buy
        ui->buyInPage->onCardDetected(uii.toHex());
        break;
    case 2:
        // manage
        break;
    }
}

void DrugSaleManageSystemMainWidget::on_openCloseBtn_clicked(bool checked)
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
