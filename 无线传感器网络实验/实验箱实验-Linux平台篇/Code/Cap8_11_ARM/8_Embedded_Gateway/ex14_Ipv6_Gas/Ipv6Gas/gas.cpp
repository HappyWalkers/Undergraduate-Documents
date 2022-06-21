#include "gas.h"
#include "ui_gas.h"
#include <QTextCodec>
#include <QDebug>
#include <QDesktopWidget>


Ipv6Gas::Ipv6Gas(const QString &ip, quint8 id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Ipv6Gas),
    funcID(id),
    wsnSrvUser(NULL)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowMinMaxButtonsHint);
    //width need to modify by liucm
    this->setGeometry(QApplication::desktop()->width()/7,QApplication::desktop()->height()/2+15
                      ,this->width(),this->height());

    this->timer = new QTimer;
    this->gasAlarmFlag = false;

    pic[0].load(":/pic/secure.png");
    pic[1].load(":/pic/gas.png");
    ui->labelPic->setPixmap(pic[0]);
    ui->labelPic->setScaledContents(true);

    connect(this, SIGNAL(nodeInfoChanged(QByteArray)), this, SLOT(updateNodeInfo(QByteArray)));
    connect(this, SIGNAL(gotNewNodeData(char)), this, SLOT(updateNodeData(char)));
    connect(this->timer, SIGNAL(timeout()), this, SLOT(timeOut()));
// modify by liucm
    ui->label_3->hide();
    ui->parAddrEdit->hide();
        ui->hwAddrEdit->hide();

    reconnect(ip, id);
}


Ipv6Gas::~Ipv6Gas()
{
    delete ui;
}

void Ipv6Gas::reconnect(const QString &ip, quint8 id)
{
    wsnSrvIp = ip;
    funcID = id;
    ipv6comm_unregister(wsnSrvUser);
    wsnSrvUser = ipv6comm_register(wsnSrvIp.toUtf8().constData(),
                    NULL, cbNewFunc, cbNewData, cbNodeGone,
                    NULL, (void *)this);

    int funcType = DevGas;

    IPV6COMM_NODE *node = ipv6comm_getNode_byType(ip.toUtf8().constData(), DevGas, funcID);
    qDebug()<<"####==Ipv6Gas==#### reconnect func id:"<<funcID;

    if(node != NULL)
    {
        this->curNwkAddr = QByteArray::fromRawData((const char *)node->nwkAddr, IPV6_ADDR_LEN);
        qDebug()<<"####==reconnect==#### nwkAddr:"<<curNwkAddr;

        updateNodeInfo(this->curNwkAddr);
        char *data = NULL;
        ipv6comm_getNodeData_byType(ip.toUtf8().constData(), funcType, funcID, &data);
        qDebug()<<"Ipv6Gas::reconnect==== DevGas data:"<<*((unsigned short *)data);
        if(data != NULL)
        {
            updateNodeData(*((unsigned short *)data));
            free(data);
        }
        ipv6comm_delete_node(node);
    }
    else
    {
        qDebug()<<"####==Ipv6Gas==#### reconnect node is null!";
        QString tmp = VALID_NWKADDR;
        this->curNwkAddr = tmp.toLocal8Bit();
        //this->curNwkAddr = QByteArray::fromHex(VALID_NWKADDR);

        updateNodeInfo(this->curNwkAddr);
    }
    QString title = QTextCodec::codecForName("UTF-8")->toUnicode(ipv6comm_find_nodeTypeString(funcType));
    title += " - ";
    if(funcID != 0xFF)
        title += QString::number(funcID);
    else
        title += tr("Any");
    this->setWindowTitle(title);
}

void Ipv6Gas::showEvent(QShowEvent *)
{
    if(wsnSrvUser == NULL)
    {
        wsnSrvUser = ipv6comm_register(wsnSrvIp.toUtf8().constData(),
                        NULL, cbNewFunc, cbNewData, cbNodeGone,
                        NULL, (void *)this);
    }
}

void Ipv6Gas::hideEvent(QHideEvent *)
{
    ipv6comm_unregister(wsnSrvUser);
    wsnSrvUser = NULL;
}

void Ipv6Gas::updateNodeInfo(QByteArray nwkAddr)
{

    qDebug()<<"Ipv6Gas::updateNodeInfo==== nwkAddr:"<<nwkAddr;
    if((nwkAddr.contains(VALID_NWKADDR)) == true)
    {
        ui->nwkAddrEdit->setText(tr("Invalid"));
        //ui->parAddrEdit->setText(tr("Invalid"));
        //ui->hwAddrEdit->setText(tr("Invalid"));
    }
    else
    {

#if     1       //by liucm
        ui->nwkAddrEdit->setText(nwkAddr.toHex());

#else
        sprintf(tmpString, "%04X", nwkAddr);
        ui->nwkAddrEdit->setText(tmpString);
        sprintf(tmpString, "%04X", parAddr);
        ui->parAddrEdit->setText(tmpString);
#endif
        //ui->hwAddrEdit->setText(QByteArray((char *)hwAddr, 8).toHex());
    }
    //qDebug()<<"Ipv6Gas::updateNodeInfo==== nwkAddr:"<<hwAddr;

}


void Ipv6Gas::updateNodeData(char v)
{
    switch(v)
    {
    case 0:
        {
            if(true == this->gasAlarmFlag)
            {
                this->gasAlarmFlag = false;
                timer->stop();
            }
            ui->labelPic->setPixmap(pic[0]);
            ui->labelPic->setScaledContents(true);
            break;
        }
    case 1:
        {
            if(false == this->gasAlarmFlag)
            {
                this->gasAlarmFlag = true;
                timer->start(20000);
                emit gotIpv6GasAlarm("gas");
            }
            ui->labelPic->setPixmap(pic[1]);
            ui->labelPic->setScaledContents(true);
        }
        break;
    default:
        ui->labelPic->setPixmap(QPixmap());
        break;
    }
}

static Ipv6Gas *gas = NULL;
void Ipv6Gas::showOut(const QString &ip, quint8 id)
{
    //qDebug()<<"Ipv6Gas::showOut==== ip:"<<ip<<"id:"<<id;

    if(gas == NULL)
        gas = new Ipv6Gas(ip);
    else
        gas->reconnect(ip, id);
    gas->show();
}

void Ipv6Gas::cbNewFunc(void *arg, unsigned char *nwkAddr, int funcNum, IPV6COMM_NODE_FUNC *funcList)
{
    Ipv6Gas *This = qobject_cast<Ipv6Gas *>((QObject *)arg);
    int funcType = DevGas;  //3;       //modify by liucm

    if(This == NULL)
        return;
    int i;
    for(i = 0; i < funcNum; i++)
    {
        if((funcList[i].funcCode == funcType) && ((This->funcID == 0xFF) || (This->funcID == funcList[i].funcID)))
        {
            IPV6COMM_NODE *node = ipv6comm_getNode_byAddr(This->wsnSrvIp.toUtf8().constData(), nwkAddr);
            if(node != NULL)
            {
                This->curNwkAddr = QByteArray::fromRawData((const char *)node->nwkAddr, IPV6_ADDR_LEN);
                emit This->nodeInfoChanged(This->curNwkAddr);
                ipv6comm_delete_node(node);
            }
        }
    }
}

void Ipv6Gas::cbNewData(void *arg, unsigned char *nwkAddr, int endPoint, int funcCode, int funcID, char *data, int len)
{
    Q_UNUSED(endPoint);Q_UNUSED(len);
    int funcType = DevGas;  //modify by liucm

    if(funcCode != funcType)
        return;
    Ipv6Gas *This = qobject_cast<Ipv6Gas *>((QObject *)arg);
    if(This == NULL)
        return;
    if((This->funcID != 0xFF) && (funcID != This->funcID))
        return;
    unsigned char validAddr[IPV6_ADDR_LEN];
        memset(validAddr, 0xFF, sizeof(validAddr));
    if(memcmp(This->curNwkAddr.data(), validAddr, sizeof(validAddr)) == 0)
    {
        IPV6COMM_NODE *node = ipv6comm_getNode_byAddr(This->wsnSrvIp.toUtf8().constData(), nwkAddr);
        if(node != NULL)
        {
            This->curNwkAddr = QByteArray::fromRawData((const char *)node->nwkAddr, IPV6_ADDR_LEN);
            emit This->nodeInfoChanged(This->curNwkAddr);
            ipv6comm_delete_node(node);
        }
        else
            emit This->nodeInfoChanged(This->curNwkAddr);
    }
    uint8 tmpVal = data[0];
    qDebug()<<"Ipv6Gas::cbNewData==== DevGas data:"<<tmpVal;
    emit This->gotNewNodeData(data[0]);
}

void Ipv6Gas::cbNodeGone(void *arg, unsigned char *nwkAddr)
{
    Ipv6Gas *This = qobject_cast<Ipv6Gas *>((QObject *)arg);
    if(This == NULL)
        return;
    if( memcmp( nwkAddr, This->curNwkAddr.data(), IPV6_ADDR_LEN) != 0 )
        return;
    This->curNwkAddr = QByteArray::fromHex(VALID_NWKADDR);
    emit This->nodeInfoChanged(This->curNwkAddr);
}
