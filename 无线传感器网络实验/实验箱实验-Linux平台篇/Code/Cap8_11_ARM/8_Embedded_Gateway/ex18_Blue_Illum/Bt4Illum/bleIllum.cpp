#include "bleIllum.h"
#include "ui_bleIllum.h"
#include <QTextCodec>
#include <QDebug>
#include <QDesktopWidget>

BleIllum::BleIllum(const QString &ip, quint8 id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BleIllum),
    funcID(id),
    wsnSrvUser(NULL)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowMinMaxButtonsHint);
    this->setGeometry(QApplication::desktop()->width()/5*2,QApplication::desktop()->height()/2+15
                      ,this->width(),this->height());

    connect(this, SIGNAL(nodeInfoChanged(QByteArray)), this, SLOT(updateNodeInfo(QByteArray)));
    connect(this, SIGNAL(gotNewNodeData(unsigned short)), this, SLOT(updateNodeData(unsigned short)));

    // modify by liucm
    ui->label_2->hide();
    ui->parAddrEdit->hide();
    ui->hwAddrEdit->hide();
    qDebug()<<"funcID:"<<id;
    reconnect(ip, id);   
}

BleIllum::~BleIllum()
{
    delete ui;
}

void BleIllum::reconnect(const QString &ip, quint8 id)
{
    wsnSrvIp = ip;
    funcID = id;
    bt4comm_unregister(wsnSrvUser);
    wsnSrvUser = bt4comm_register(wsnSrvIp.toUtf8().constData(),
                    NULL, cbNewFunc, cbNewData, cbNodeGone,
                    NULL, (void *)this);
    int funcType = DevILLum;
    BT4COMM_NODE *node = bt4comm_getNode_byType(ip.toUtf8().constData(), funcType, funcID);
    if(node != NULL)
    {
        //curNwkAddr = node->nwkAddr;
        this->curNwkAddr = QByteArray::fromRawData((const char *)node->nwkAddr, BT_ADDR_LEN);

        updateNodeInfo(this->curNwkAddr);
        char *data = NULL;
        bt4comm_getNodeData_byType(ip.toUtf8().constData(), funcType, funcID, &data);
        if( data != NULL)
            qDebug()<<"BtIllum::reconnect==== DevIllum data:"<<*((unsigned short *)data);
        else
            qDebug()<<"BtIllum::reconnect==== DevIllum data err!!";
        if(data != NULL)
        {
            updateNodeData(*((unsigned short *)data));
            free(data);
        }
        bt4comm_delete_node(node);
    }
    else
    {
        //curNwkAddr = 0xFFFF;
        qDebug()<<"####==BtIllum==#### reconnect node is null!";
        QString tmp = VALID_NWKADDR;
        this->curNwkAddr = tmp.toLocal8Bit();
        updateNodeInfo(this->curNwkAddr);
    }
    QString title = QTextCodec::codecForName("UTF-8")->toUnicode(bt4comm_find_nodeTypeString(funcType));
    title += " - ";
    if(funcID != 0xFF)
        title += QString::number(funcID);
    else
        title += tr("Any");
    this->setWindowTitle(title);
}

void BleIllum::showEvent(QShowEvent *)
{
    if(wsnSrvUser == NULL)
    {
        wsnSrvUser = bt4comm_register(wsnSrvIp.toUtf8().constData(),
                        NULL, cbNewFunc, cbNewData, cbNodeGone,
                        NULL, (void *)this);
    }
}

void BleIllum::hideEvent(QHideEvent *)
{
    bt4comm_unregister(wsnSrvUser);
    wsnSrvUser = NULL;
}

void BleIllum::updateNodeInfo(QByteArray nwkAddr)
{
    //if(nwkAddr == 0xFFFF)
    if((nwkAddr.contains(VALID_NWKADDR)) == true)
    {
        ui->nwkAddrEdit->setText(tr("Invalid"));
        //ui->parAddrEdit->setText(tr("Invalid"));
        //ui->hwAddrEdit->setText(tr("Invalid"));
	ui->valueEdit->setText(tr("Invalid"));
    }
    else
    {
        //char tmpString[20];
        //sprintf(tmpString, "%04X", nwkAddr);
        //ui->nwkAddrEdit->setText(tmpString);
        //sprintf(tmpString, "%04X", parAddr);
        //ui->parAddrEdit->setText(tmpString);
        //ui->hwAddrEdit->setText(QByteArray((char *)hwAddr, 8).toHex());
        ui->nwkAddrEdit->setText(nwkAddr.toHex());
    }
    //qDebug()<<"bleIllum::updateNodeInfo==== nwkAddr:"<<hwAddr;
}


void BleIllum::updateNodeData(unsigned short temp)
{
    float v = float(temp) / 100;
    ui->valueEdit->setText(QString::number(v));
}

static BleIllum *light = NULL;
void BleIllum::showOut(const QString &ip, quint8 id)
{
    if(light == NULL)
        light = new BleIllum(ip, id);
    else
        light->reconnect(ip, id);
    light->show();
}

void BleIllum::cbNewFunc(void *arg, unsigned char *nwkAddr, int funcNum, BT4COMM_NODE_FUNC *funcList)
{
    BleIllum *This = qobject_cast<BleIllum *>((QObject *)arg);
    uint8   curaddrType = BTCOMM_ADDRTYPE;
    if(This == NULL)
        return;
    int i;
    for(i = 0; i < funcNum; i++)
    {
        if((funcList[i].funcCode == DevILLum) && ((This->funcID == 0xFF) || (This->funcID == funcList[i].funcID)))
        {
            BT4COMM_NODE *node = bt4comm_getNode_byAddr(This->wsnSrvIp.toUtf8().constData(), nwkAddr, curaddrType);
            if(node != NULL)
            {

                This->curNwkAddr = QByteArray::fromRawData((const char *)node->nwkAddr, BT_ADDR_LEN);
                emit This->nodeInfoChanged(This->curNwkAddr);
                bt4comm_delete_node(node);
            }
        }
    }
}

void BleIllum::cbNewData(void *arg, unsigned char *nwkAddr, int endPoint, int funcCode, int funcID, char *data, int len)
{
    Q_UNUSED(endPoint);Q_UNUSED(len);
    uint8   curaddrType = BTCOMM_ADDRTYPE;
    if(funcCode != DevILLum)
        return;
    BleIllum *This = qobject_cast<BleIllum *>((QObject *)arg);
    if(This == NULL)
        return;
    if((This->funcID != 0xFF) && (funcID != This->funcID))
        return;
    unsigned char validAddr[BT_ADDR_LEN];
    memset(validAddr, 0xFF, sizeof(validAddr));
    if(memcmp(This->curNwkAddr.data(), validAddr, sizeof(validAddr)) == 0)
    //if(This->curNwkAddr == 0xFFFF)
    {
        BT4COMM_NODE *node = bt4comm_getNode_byAddr(This->wsnSrvIp.toUtf8().constData(), nwkAddr, curaddrType);
        if(node != NULL)
        {
            This->curNwkAddr = QByteArray::fromRawData((const char *)node->nwkAddr, BT_ADDR_LEN);
            emit This->nodeInfoChanged(This->curNwkAddr);
            bt4comm_delete_node(node);
        }
        else
            emit This->nodeInfoChanged(This->curNwkAddr);
    }
    unsigned short v = *((unsigned short *)data);
    emit This->gotNewNodeData(v);
}

void BleIllum::cbNodeGone(void *arg, unsigned char *nwkAddr)
{
    BleIllum *This = qobject_cast<BleIllum *>((QObject *)arg);
    if(This == NULL)
        return;
    if( memcmp( nwkAddr, This->curNwkAddr.data(), BT_ADDR_LEN) != 0 )
        return;
    This->curNwkAddr = QByteArray::fromHex(VALID_NWKADDR);
    emit This->nodeInfoChanged(This->curNwkAddr);
}

