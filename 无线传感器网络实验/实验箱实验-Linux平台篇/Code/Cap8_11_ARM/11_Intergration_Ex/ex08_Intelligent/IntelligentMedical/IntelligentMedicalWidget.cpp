#include "IntelligentMedicalWidget.h"
#include "ui_IntelligentMedicalWidget.h"
#include <libipv6comm.h>
#include <libbt4comm.h>
#include <libwsncomm.h>
#include <libsmscb.h>
#define MAIN_NODE_CONFIG
#include <node_config.h>
#include <QDebug>


#define WSN_EXECUTEB_ID     3
IntelligentMedicalWidget::IntelligentMedicalWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IntelligentMedicalWidget),
    irSmsFlag(false), gasSmsFlag(false),
    _minThreshold(10.0), _maxThreshold(35.0),
    wsnUser(NULL),ipv6User(NULL),bt4User(NULL)
{
    ui->setupUi(this);
    ui->irSensorLabel->startTwinkling(800);
    ui->currentPhoneNumber->setText("");
    ui->alarmPhoneEdit->setText("");

    connect(this, SIGNAL(gotSaftyData(bool)), this, SLOT(onGotSaftyData(bool)));
    connect(this, SIGNAL(gotGasData(bool)), this, SLOT(onGotGasData(bool)));
    connect(this, SIGNAL(gotExecuteBData(char)), this, SLOT(onGotExecuteBData(char)));
    connect(this, SIGNAL(gotRainData(bool)), this, SLOT(onGotRainData(bool)));
    connect(this, SIGNAL(gotIllumData(unsigned short)), this, SLOT(onGotIllumData(unsigned short)));
    connect(this, SIGNAL(gotHallData(bool)), this, SLOT(onGotHallData(bool)));

    ipv6User = ipv6comm_register("127.0.0.1", NULL, NULL, (IPV6CB_NEW_DATA)ipv6cbNewData, NULL, NULL, this);
    wsnUser = wsncomm_register("127.0.0.1", NULL, NULL, (CB_NEW_DATA)cbNewData, NULL, NULL, this);
    bt4User = bt4comm_register("127.0.0.1", NULL, NULL, (BTCB_NEW_DATA)bt4cbNewData, NULL, NULL, this);

}

IntelligentMedicalWidget::~IntelligentMedicalWidget()
{
    if(wsnUser != NULL)
        ipv6comm_unregister(wsnUser);
    if(ipv6User != NULL)
        ipv6comm_unregister(ipv6User);
    if(bt4User != NULL)
        ipv6comm_unregister(bt4User);
    delete ui;
}

void IntelligentMedicalWidget::ipv6cbNewData(IntelligentMedicalWidget *This, unsigned char *nwkAddr, int endpoint, int funcCode, int funcID, char *data, int len)
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


void IntelligentMedicalWidget::cbNewData(IntelligentMedicalWidget *This, unsigned short nwkAddr, int endpoint, int funcCode, int funcID, char *data, int len)
{
    Q_UNUSED(nwkAddr);Q_UNUSED(endpoint);Q_UNUSED(funcID);Q_UNUSED(len);
    if(This == NULL)
        return;
    switch(funcCode)
    {
    case DevExecuteB:
        emit This->gotExecuteBData(data[0]);
        break;
    case DevRain:
        emit This->gotRainData(!!data[0]);
        break;
    }
}

void IntelligentMedicalWidget::bt4cbNewData(IntelligentMedicalWidget *This, unsigned char *nwkAddr, int endpoint, int funcCode, int funcID, char *data, int len)
{
    Q_UNUSED(nwkAddr);Q_UNUSED(endpoint);Q_UNUSED(funcID);Q_UNUSED(len);
    if(This == NULL)
        return;

    unsigned short val = *((unsigned short *)data);
    switch(funcCode)
    {
        case DevILLum:
            emit This->gotIllumData(val);
            break;
        case DevHall:
            emit This->gotHallData(!!data[0]);
            break;
    }
}
void IntelligentMedicalWidget::onSoftKeyClicked()
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

void IntelligentMedicalWidget::onGotSaftyData(bool stat)
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

void IntelligentMedicalWidget::onGotGasData(bool stat)
{
    char *data = NULL;
    char excutv = 0;
    wsncomm_getNodeData_byType("127.0.0.1", DevExecuteB, WSN_EXECUTEB_ID, &data);
    if(data != NULL)
    {
        excutv = *((unsigned short *)data);
        free(data);
    }

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
            excutv |= 0x02;         //open window
            openWindFlag = true;
        }
    }
    else
    {
        if(ui->gasSensorLabel->isTwinkling())
            ui->gasSensorLabel->stopTwinkling();
        gasSmsFlag = false;
     }
}

//rain node
void IntelligentMedicalWidget::onGotRainData(bool stat)
{
    char *data=NULL;
    char excutv = 0;
    wsncomm_getNodeData_byType("127.0.0.1", DevExecuteB, WSN_EXECUTEB_ID, &data);
    if(data != NULL)
    {
        excutv = *((unsigned short *)data);
        free(data);
    }
    if(stat)
    {
        if(!ui->rainSensorLabel->isTwinkling())
            ui->rainSensorLabel->startTwinkling();
        if(ui->currentPhoneNumber->text().isEmpty())
            return;
        if(!rainSmsFlag)
        {
            rainSmsFlag = true;
            qDebug()<<"the alarm send string is raining, please close window!!!";
            SMSCB_SendSMS("127.0.0.1", ui->currentPhoneNumber->text().toAscii(), "raining, please close window!!!");
            if(gasSmsFlag == true)
                return;

            excutv &= ~0x02;                //close window
            openWindFlag = false;
        }
    }
    else
    {
        if(ui->rainSensorLabel->isTwinkling())
            ui->rainSensorLabel->stopTwinkling();
        rainSmsFlag = false;

        excutv |= 0x02;         //open window
        openWindFlag = true;
    }
    wsncomm_sendNode_byType("127.0.0.1", DevExecuteB, WSN_EXECUTEB_ID, &excutv, 1);
}

void IntelligentMedicalWidget::onGotHallData(bool stat)
{
    char *data=NULL;
    char excutv = 0;
    wsncomm_getNodeData_byType("127.0.0.1", DevExecuteB, WSN_EXECUTEB_ID, &data);
    if(data != NULL)
    {
        excutv = *((unsigned short *)data);
        free(data);
    }

    if(stat)
    {
        if(!ui->hallSensorLabel->isTwinkling())
            ui->hallSensorLabel->startTwinkling();
        if(ui->currentPhoneNumber->text().isEmpty())
            return;
        if(!hallSmsFlag)
        {
            hallSmsFlag = true;
            qDebug()<<"the alarm send string is Radiation Pollution!!!";
            SMSCB_SendSMS("127.0.0.1", ui->currentPhoneNumber->text().toAscii(), "Radiation Pollution!!!");
            excutv |= 0x08;
        }
    }
    else
    {
        if(ui->hallSensorLabel->isTwinkling())
            ui->hallSensorLabel->stopTwinkling();
        hallSmsFlag = false;
        excutv &= ~0x08;            //close alarm
    }

    wsncomm_sendNode_byType("127.0.0.1", DevExecuteB, WSN_EXECUTEB_ID, &excutv, 1);

}



//get illum light
void IntelligentMedicalWidget::onGotIllumData(unsigned short illum)
{

    qDebug()<<"####==update Illum Data==#### data:"<<illum;
    float illv = float(illum) / 100;
    char *data=NULL;
    char excutv = 0;
    wsncomm_getNodeData_byType("127.0.0.1", DevExecuteB, WSN_EXECUTEB_ID, &data);
    if(data != NULL)
    {
        excutv = *((unsigned short *)data);
        free(data);
    }

    ui->illumDisplay->setText(QString::number(illv));
    if(illv > _maxThreshold){
        openLampFlag = false;
        excutv &= ~0x01;        //close lamp
    }
    else if(illv < _minThreshold){
        openLampFlag = true;
        excutv |= 0x01;        //open lamp
    }
    wsncomm_sendNode_byType("127.0.0.1", DevExecuteB, WSN_EXECUTEB_ID, &excutv, 1);
}


//get execute
void IntelligentMedicalWidget::onGotExecuteBData(char exectue)
{

    qDebug()<<"####==update ExecuteB Data==#### data:"<<exectue;

}



void IntelligentMedicalWidget::on_pushButton_clicked()
{
    ui->currentPhoneNumber->setText(ui->alarmPhoneEdit->text());

    if(ui->minLightValue->value() < ui->maxLightValue->value()){
        _minThreshold  = ui->minLightValue->value();
        _maxThreshold  = ui->maxLightValue->value();
    }
    else{
        _minThreshold  = ui->maxLightValue->value();
        _maxThreshold  = ui->minLightValue->value();
    }
}

