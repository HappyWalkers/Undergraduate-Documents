#include "wifi.h"
#include "ui_wifi.h"
#include <libwificomm.h>
#include <node_config.h>
#include <QTimer>
#include <QDebug>

float Wifi::_lastTempValue = 0.0;
float Wifi::_lastHumiValue = 0.0;
Wifi *Wifi::_instance = NULL;
Wifi::Wifi(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Wifi),
    wifiSrvIp("127.0.0.1"),
    wifiCommUser(NULL)
{
    ui->setupUi(this);
    connect(this, SIGNAL(newData(QString,int,int,int,QByteArray)), this, SLOT(updateNewData(QString,int,int,int,QByteArray)));
    connect(this, SIGNAL(serverGone()), this, SLOT(reconnect()));

    ui->tempLabel->setRange(-10,50);
    ui->tempLabel->setTmpFile("wifi_temp");

    ui->HumiLabel->setRange(0,100);
    ui->HumiLabel->setTmpFile("wifi_humi");

    wifiConnTimer = new QTimer(this);
    wifiConnTimer->setInterval(3000);
    wifiConnTimer->setSingleShot(true);
    connect(wifiConnTimer, SIGNAL(timeout()), this, SLOT(reconnect()));

    updateTimer = new QTimer(this);
    updateTimer->setInterval(1000);
    updateTimer->setSingleShot(false);
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(onUpdate()));
    updateTimer->start();
}

Wifi::~Wifi()
{
    wificomm_unregister(wifiCommUser);
    delete wifiConnTimer;
    delete ui;
}

void Wifi::reconnect()
{
    wificomm_unregister(wifiCommUser);
    wifiCommUser = NULL;
    wifiCommUser = wificomm_register(wifiSrvIp.toUtf8().constData(), NULL, onNewData, NULL, onServerGone, this);
    if(wifiCommUser == NULL)
        wifiConnTimer->start();
}

void Wifi::disconnect()
{
    wificomm_unregister(wifiCommUser);
    wifiCommUser = NULL;
}

void Wifi::reconnect(const QString &ip)
{
    wifiSrvIp = ip;
    reconnect();
}

void Wifi::showEvent(QShowEvent *)
{
    reconnect();
}

void Wifi::hideEvent(QHideEvent *)
{
    disconnect();
}

void Wifi::updateNewData(const QString &ip, int endPoint, int funcCode, int funcID, const QByteArray &data)
{
    Q_UNUSED(ip);Q_UNUSED(endPoint);Q_UNUSED(funcID);
    quint16 v = 0;
    memcpy(&v, data.constData(), 2);
    switch(funcCode)
    {
    case DevTemp:
        _lastTempValue = float(v) / 100;
        break;
    case DevHumm:
        _lastHumiValue = float(v) / 100;
        break;
    }
}

void Wifi::onUpdate()
{
    ui->tempLabel->addData(_lastTempValue);
    ui->HumiLabel->addData(_lastHumiValue);
}

void Wifi::onNewData(void *arg, const char *nodeIP, int endPoint, int funcCode, int funcID, char *data, int len)
{
    qDebug()<<"NEW DATA>>>>>>>>>>>>>>>>>"<<nodeIP<<endPoint<<funcCode<<funcID;
    Wifi *This = qobject_cast<Wifi*>((QObject*)arg);
    if(This == NULL)
        return;
    QByteArray d(data, len);
    emit This->newData(nodeIP, endPoint, funcCode, funcID, QByteArray(data, len));
}

void Wifi::onServerGone(void *arg)
{
    Wifi *This = qobject_cast<Wifi*>((QObject*)arg);
    if(This == NULL)
        return;
    emit This->serverGone();
}
