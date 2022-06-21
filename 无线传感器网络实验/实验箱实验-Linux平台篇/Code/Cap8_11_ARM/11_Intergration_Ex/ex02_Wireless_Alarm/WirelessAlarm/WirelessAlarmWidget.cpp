#include "WirelessAlarmWidget.h"
#include "ui_WirelessAlarmWidget.h"
#include <libipv6comm.h>
#include <libsmscb.h>
#define MAIN_NODE_CONFIG
#include <node_config.h>
#include <QDebug>

WirelessAlarmWidget::WirelessAlarmWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WirelessAlarmWidget),
    irSmsFlag(false), gasSmsFlag(false),
    wsnUser(NULL)
{
    ui->setupUi(this);
    ui->irSensorLabel->startTwinkling(800);
    ui->currentPhoneNumber->setText("");
    ui->alarmPhoneEdit->setText("");

    connect(this, SIGNAL(gotSaftyData(bool)), this, SLOT(onGotSaftyData(bool)));
    connect(this, SIGNAL(gotGasData(bool)), this, SLOT(onGotGasData(bool)));

    wsnUser = ipv6comm_register("127.0.0.1", NULL, NULL, (IPV6CB_NEW_DATA)cbNewData, NULL, NULL, this);

}

WirelessAlarmWidget::~WirelessAlarmWidget()
{
    if(wsnUser != NULL)
        ipv6comm_unregister(wsnUser);
    delete ui;
}

void WirelessAlarmWidget::cbNewData(WirelessAlarmWidget *This, unsigned short nwkAddr, int endpoint, int funcCode, int funcID, char *data, int len)
{
    Q_UNUSED(nwkAddr);Q_UNUSED(endpoint);Q_UNUSED(funcID);Q_UNUSED(len);
    if(This == NULL)
        return;
    switch(funcCode)
    {
    case DevIRPers:
        emit This->gotSaftyData(!!data[0]);
        break;
    case DevGas:
        emit This->gotGasData(!!data[0]);
        break;
    }
}

void WirelessAlarmWidget::onSoftKeyClicked()
{
    QPushButton *btn = qobject_cast<QPushButton *>(sender());
    if(btn == NULL)
        return;
    if(btn->text() == "<-")
        ui->alarmPhoneEdit->backspace();
//    {
//        QString t = ui->alarmPhoneEdit->text();
//        ui->alarmPhoneEdit->setText(t.left(t.length() - 1));
//    }
    else
        ui->alarmPhoneEdit->insert(btn->text());
}

void WirelessAlarmWidget::onGotSaftyData(bool stat)
{
    if(stat)
    {
        if(!ui->irSensorLabel->isTwinkling())
            ui->irSensorLabel->startTwinkling();
        if(ui->currentPhoneNumber->text().isEmpty())
            return;
        if(!irSmsFlag)
        {
            irSmsFlag = true;
            qDebug()<<"the alarm send string is Some body crack into your house!!!";
            SMSCB_SendSMS("127.0.0.1", ui->currentPhoneNumber->text().toAscii(), "Some body crack into your house!!!");
        }
    }
    else
    {
        if(ui->irSensorLabel->isTwinkling())
            ui->irSensorLabel->stopTwinkling();
        irSmsFlag = false;
    }
}

void WirelessAlarmWidget::onGotGasData(bool stat)
{
    if(stat)
    {
        if(!ui->gasSensorLabel->isTwinkling())
            ui->gasSensorLabel->startTwinkling();
        if(ui->currentPhoneNumber->text().isEmpty())
            return;
        if(!gasSmsFlag)
        {
            gasSmsFlag = true;
            qDebug()<<"the alarm send string is Gas leaking!!!";
            SMSCB_SendSMS("127.0.0.1", ui->currentPhoneNumber->text().toAscii(), "Gas leaking!!!");
        }
    }
    else
    {
        if(ui->gasSensorLabel->isTwinkling())
            ui->gasSensorLabel->stopTwinkling();
        gasSmsFlag = false;
     }
}

void WirelessAlarmWidget::on_pushButton_clicked()
{
    ui->currentPhoneNumber->setText(ui->alarmPhoneEdit->text());
}
