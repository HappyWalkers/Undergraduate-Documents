#include "wifinet.h"
#include "ui_wifinet.h"
#include <QFile>
#include <unistd.h>
#include <stdio.h>
#include <QMessageBox>
#include <QTextCodec>
#include <QDebug>
#include <QTreeWidgetItem>
#include <QTimer>
#define MAIN_NODE_CONFIG
#include <node_config.h>

float WifiNet::_lastTempValue = 0.0;
float WifiNet::_lastHumiValue = 0.0;
WifiNet *WifiNet::_instance = NULL;
WifiNet::WifiNet(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WifiNet),
    wifiSrvIp("127.0.0.1"), wifiCommUser(NULL), wifiConnTimer(NULL)
{
    ui->setupUi(this);
	connect(this, SIGNAL(newNode(QString,int,WIFI_NODE_FUNC*)), this, SLOT(updateNewNode(QString,int,WIFI_NODE_FUNC*)));
	connect(this, SIGNAL(newData(QString,int,int,int,QByteArray)), this, SLOT(updateNewData(QString,int,int,int,QByteArray)));
	connect(this, SIGNAL(nodeGone(QString)), this, SLOT(deleteNode(QString)));
	connect(this, SIGNAL(serverGone()), this, SLOT(reconnect()));

	wifiConnTimer = new QTimer(this);
	wifiConnTimer->setInterval(3000);
	wifiConnTimer->setSingleShot(true);
	connect(wifiConnTimer, SIGNAL(timeout()), this, SLOT(reconnect()));
}

WifiNet::~WifiNet()
{
	wificomm_unregister(wifiCommUser);
	delete wifiConnTimer;
    delete ui;
}

void WifiNet::reconnect()
{
	wificomm_unregister(wifiCommUser);
	wifiCommUser = NULL;
	wifiCommUser = wificomm_register(wifiSrvIp.toUtf8().constData(), onNewNode, onNewData, onNodeGone, onServerGone, this);
	ui->nodeList->setEnabled(wifiCommUser != NULL);
	if(wifiCommUser == NULL)
		wifiConnTimer->start();
	ui->nodeList->clear();
}

void WifiNet::disconnect()
{
	wificomm_unregister(wifiCommUser);
	wifiCommUser = NULL;
}

void WifiNet::reconnect(const QString &ip)
{
	wifiSrvIp = ip;
	reconnect();
}

void WifiNet::showEvent(QShowEvent *)
{
	reconnect();
}

void WifiNet::hideEvent(QHideEvent *)
{
	disconnect();
}

QTreeWidgetItem *WifiNet::createItem(const QString &ip, int endPoint, int funcCode, int funcID)
{
	QTreeWidgetItem * item = findItem(ip, endPoint);
	if(item == NULL)
		item = new QTreeWidgetItem(ui->nodeList);
	item->setText(0, ip);
	const char *type = wsncomm_find_nodeTypeString(funcCode);
	if(type == NULL)
		item->setText(1, tr("Unknown"));
	else
		item->setText(1, QTextCodec::codecForName("UTF8")->toUnicode(type));
	item->setText(2, QString::number(funcID));
	item->setText(3, "");
	item->setData(0, Qt::UserRole, endPoint);
	return item;
}

QTreeWidgetItem *WifiNet::findItem(const QString &ip, int endPoint)
{
	QList<QTreeWidgetItem*> items = ui->nodeList->findItems(ip, Qt::MatchExactly);

	for(int i = 0; i < items.size(); i++)
	{
		if(items.at(i)->data(0, Qt::UserRole).toInt() == endPoint)
			return items.at(i);
	}
	return NULL;
}

void WifiNet::updateNewNode(const QString &ip, int funcNum, WIFI_NODE_FUNC *funcList)
{
	for(int i = 0; i < funcNum; i++)
	{
            if((funcList[i].funcCode == DevTemp)||(funcList[i].funcCode == DevHumm))  //只显示温湿度数据
		createItem(ip, i + 1, funcList[i].funcCode, funcList[i].funcID);
	}
	wificomm_delete_funclist(funcList);
}

void WifiNet::updateNewData(const QString &ip, int endPoint, int funcCode, int funcID, const QByteArray &data)
{
	QTreeWidgetItem *item = findItem(ip, endPoint);
        if((item == NULL)&&( ((funcCode == DevHumm)||(funcCode == DevTemp))))
        {
                item = createItem(ip, endPoint, funcCode, funcID);
        }

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
        case DevHall:
        case DevShake:
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
        qDebug()<<"NEW Data=======funcCode:"<<funcCode<<";data:"<< val;
        if(item != NULL)
            item->setText(3, val);
}

void WifiNet::deleteNode(const QString &ip)
{
	QList<QTreeWidgetItem*> items = ui->nodeList->findItems(ip, Qt::MatchExactly);
	for(int i = 0; i < items.size(); i++)
	{
		delete items.at(i);
	}
}

void WifiNet::onNewNode(void *arg, const char *nodeIP, int funcNum, WIFI_NODE_FUNC *funcList)
{
	qDebug()<<"NEW NODE>>>>>>>>>>>>>>>>>>"<<nodeIP;
	WifiNet *This = qobject_cast<WifiNet*>((QObject*)arg);
	if(This == NULL)
		return;
	WIFI_NODE_FUNC *f = wificomm_funclist_dup(funcList, funcNum);
	emit This->newNode(nodeIP, funcNum, f);
}

void WifiNet::onNewData(void *arg, const char *nodeIP, int endPoint, int funcCode, int funcID, char *data, int len)
{
	qDebug()<<"NEW DATA>>>>>>>>>>>>>>>>>"<<nodeIP<<endPoint<<funcCode<<funcID;
	WifiNet *This = qobject_cast<WifiNet*>((QObject*)arg);
	if(This == NULL)
		return;
	QByteArray d(data, len);
	emit This->newData(nodeIP, endPoint, funcCode, funcID, QByteArray(data, len));
}

void WifiNet::onNodeGone(void *arg, const char *nodeIP)
{
	qDebug()<<"NODE GONE>>>>>>>>>>>>>>>>>>"<<nodeIP;
	WifiNet *This = qobject_cast<WifiNet*>((QObject*)arg);
	if(This == NULL)
		return;
	emit This->nodeGone(nodeIP);
}

void WifiNet::onServerGone(void *arg)
{
	WifiNet *This = qobject_cast<WifiNet*>((QObject*)arg);
	if(This == NULL)
		return;
	emit This->serverGone();
}
