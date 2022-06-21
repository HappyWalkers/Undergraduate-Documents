#include "widget.h"
#include "ui_widget.h"
#include <node_config.h>
#include <QByteArray>
#include <QTimer>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    wifiSrvIp("127.0.0.1"), wifiCommUser(NULL), wifiConnTimer(NULL)
{
    ColdStorageSetting::Create();
    ui->setupUi(this);

    connect(this, SIGNAL(newNode(QString,int,WIFI_NODE_FUNC*)), this, SLOT(updateNewNode(QString,int,WIFI_NODE_FUNC*)));
    connect(this, SIGNAL(newData(QString,int,int,int,QByteArray)), this, SLOT(updateNewData(QString,int,int,int,QByteArray)));
    connect(this, SIGNAL(nodeGone(QString)), this, SLOT(deleteNode(QString)));
    connect(this, SIGNAL(serverGone()), this, SLOT(reconnect()));

    connect(this, SIGNAL(newTempNodeValue(QString,int,int,float)),
            ui->realTimePage, SLOT(updataNodeInfo(QString,int,int,float)));
    connect(this, SIGNAL(newTempNodeValue(QString,int,int,float)),
            ui->historyPage, SLOT(updataNodeInfo(QString,int,int,float)));
    connect(this, SIGNAL(newTempNodeValue(QString,int,int,float)),
            ui->ctrlSettingPage, SLOT(updataNodeInfo(QString,int,int,float)));

    wifiConnTimer = new QTimer(this);
    wifiConnTimer->setInterval(3000);
    wifiConnTimer->setSingleShot(true);
    connect(wifiConnTimer, SIGNAL(timeout()), this, SLOT(reconnect()));
}

Widget::~Widget()
{
    wificomm_unregister(wifiCommUser);
    delete wifiConnTimer;
    delete ui;
    ColdStorageSetting::Destroy();
}

void Widget::reconnect()
{
    wificomm_unregister(wifiCommUser);
    wifiCommUser = NULL;
    wifiCommUser = wificomm_register(wifiSrvIp.toUtf8().constData(), onNewNode, onNewData, onNodeGone, onServerGone, this);
//    ui->nodeList->setEnabled(wifiCommUser != NULL);
    if(wifiCommUser == NULL)
        wifiConnTimer->start();
//    ui->nodeList->clear();
}

void Widget::disconnect()
{
    wificomm_unregister(wifiCommUser);
    wifiCommUser = NULL;
}

void Widget::reconnect(const QString &ip)
{
    wifiSrvIp = ip;
    reconnect();
}

void Widget::updateNewNode(const QString &ip, int funcNum, WIFI_NODE_FUNC *funcList)
{
    Q_UNUSED(ip);Q_UNUSED(funcNum);
#if 0
    for(int i = 0; i < funcNum; i++)
    {
        createItem(ip, i + 1, funcList[i].funcCode, funcList[i].funcID);
    }
#endif
    wificomm_delete_funclist(funcList);
}

void Widget::updateNewData(const QString &ip, int endPoint, int funcCode, int funcID, const QByteArray &data)
{
    switch(funcCode)
    {
    case DevTemp:
        {
            quint16 v = 0;
            memcpy(&v, data.constData(), 2);
            emit newTempNodeValue(ip, endPoint, funcID, float(v) / 100);
        }
        break;
    }

#if 0
    QTreeWidgetItem *item = findItem(ip, endPoint);
    if(item == NULL)
        item = createItem(ip, endPoint, funcCode, funcID);
    QString val;
    switch(funcCode)
    {
    case DevTemp:
    case DevHumm:
    case DevILLum:
    case DevIRDist:
        {
            quint16 v = 0;
            memcpy(&v, data.constData(), 2);
            val = QString::number(float(v) / 100);
        }
        break;
    case DevRain:
    case DevGas:
    case DevSmoke:
    case DevFire:
    case DevIRPers:
    case DevVoice:
        val = QString::number(!!data.at(0));
        break;
    case DevExecuteB:
    case DevRemoter:
    case Dev125kReader:
    default:
    case DevSpeaker:
        val = data.toHex();
        break;
    }

    item->setText(3, val);
#endif
}

void Widget::deleteNode(const QString &ip)
{
    Q_UNUSED(ip);
#if 0
    QList<QTreeWidgetItem*> items = ui->nodeList->findItems(ip, Qt::MatchExactly);
    for(int i = 0; i < items.size(); i++)
    {
        delete items.at(i);
    }
#endif
}

void Widget::onNewNode(void *arg, const char *nodeIP, int funcNum, WIFI_NODE_FUNC *funcList)
{
    qDebug()<<"NEW NODE>>>>>>>>>>>>>>>>>>"<<nodeIP;
    Widget *This = qobject_cast<Widget*>((QObject*)arg);
    if(This == NULL)
        return;
    WIFI_NODE_FUNC *f = wificomm_funclist_dup(funcList, funcNum);
    emit This->newNode(nodeIP, funcNum, f);
}

void Widget::onNewData(void *arg, const char *nodeIP, int endPoint, int funcCode, int funcID, char *data, int len)
{
    qDebug()<<"NEW DATA>>>>>>>>>>>>>>>>>"<<nodeIP<<endPoint<<funcCode<<funcID;
    Widget *This = qobject_cast<Widget*>((QObject*)arg);
    if(This == NULL)
        return;
//    QByteArray d(data, len);
    emit This->newData(nodeIP, endPoint, funcCode, funcID, QByteArray(data, len));
}

void Widget::onNodeGone(void *arg, const char *nodeIP)
{
    qDebug()<<"NODE GONE>>>>>>>>>>>>>>>>>>"<<nodeIP;
    Widget *This = qobject_cast<Widget*>((QObject*)arg);
    if(This == NULL)
        return;
    emit This->nodeGone(nodeIP);
}

void Widget::onServerGone(void *arg)
{
    Widget *This = qobject_cast<Widget*>((QObject*)arg);
    if(This == NULL)
        return;
    emit This->serverGone();
}

void Widget::on_openCloseBtn_clicked(bool checked)
{
    if(checked)
    {
        ui->openCloseBtn->setText(tr("Opened"));
        ui->openCloseBtn->setIcon(QIcon(":/pic/shut_down_normal.png"));
        reconnect();
    }
    else
    {
        ui->openCloseBtn->setText(tr("Closed"));
        ui->openCloseBtn->setIcon(QIcon(":/pic/shut_down_grayed.png"));
        disconnect();
    }
}
