#include "secure.h"
#include "ui_secure.h"
#include <QTextCodec>
#include <QDebug>
#include <QDesktopWidget>

Ipv6Secure::Ipv6Secure(const QString &ip, quint8 id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Ipv6Secure),
    funcID(id),
    wsnSrvUser(NULL)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowMinMaxButtonsHint);
    //width need to modify by liucm
    //this->setGeometry(10,40,this->width(),this->height());
    this->setGeometry(QApplication::desktop()->width()/5*4-270,QApplication::desktop()->height()/2+15
                      ,this->width(),this->height());

    PicTimer = new QTimer();
    connect(PicTimer,SIGNAL(timeout()),this,SLOT(PicTimeout()));
    pic[0].load(":/pic/safe.png");
    pic[1].load(":/pic/human.png");
    ui->labelPic->setPixmap(pic[0]);
    ui->labelPic->setScaledContents(true);

    connect(this, SIGNAL(nodeInfoChanged(QByteArray)), this, SLOT(updateNodeInfo(QByteArray)));
    connect(this, SIGNAL(dataChanged(char)), this, SLOT(updateNodeData(char)));

    // modify by liucm
    ui->label_2->hide();
    ui->parAddrEdit->hide();
        ui->hwAddrEdit->hide();

    reconnect(ip, id);
}

Ipv6Secure::~Ipv6Secure()
{
    if(PicTimer)
        delete PicTimer;
    delete ui;
}

void Ipv6Secure::reconnect(const QString &ip, quint8 id)
{
    int functype;

        wsnSrvIp = ip;
        funcID = id;
    ipv6comm_unregister(wsnSrvUser);
    wsnSrvUser = ipv6comm_register(wsnSrvIp.toUtf8().constData(),
                NULL, cbNewFunc, cbNewData, cbNodeGone,
                NULL, (void *)this);

    functype = DevIRPers;
    qDebug()<<"Ipv6Secure::reconnect==== DevIRPers:"<<functype<<";funcID:"<<funcID;

    IPV6COMM_NODE *node = ipv6comm_getNode_byType(ip.toUtf8().constData(), functype, funcID);
    if(node != NULL)
    {
        this->curNwkAddr = QByteArray::fromRawData((const char *)node->nwkAddr, IPV6_ADDR_LEN);
        updateNodeInfo(this->curNwkAddr);
        char *data = NULL;
        ipv6comm_getNodeData_byType(ip.toUtf8().constData(), functype, funcID, &data);
 qDebug()<<"Ipv6Secure::reconnect==== DevIRPers data:"<<data[0];
        if(data != NULL)
        {
            updateNodeData(data[0]);
            free(data);
        }
        ipv6comm_delete_node(node);
    }
    else
    {
        QString tmp = VALID_NWKADDR;
        this->curNwkAddr = tmp.toLocal8Bit();
        //this->curNwkAddr = QByteArray::fromHex(VALID_NWKADDR);

        updateNodeInfo(this->curNwkAddr);
    }
    QString title = QTextCodec::codecForName("UTF-8")->toUnicode(ipv6comm_find_nodeTypeString(functype));
    title += " - ";
    if(funcID != 0xFF)
        title += QString::number(funcID);
    else
        title += tr("Any");
    this->setWindowTitle(title);
}

void Ipv6Secure::updateNodeInfo(QByteArray nwkAddr)
{
    qDebug()<<"Ipv6Secure::updateNodeInfo==== nwkAddr:"<<nwkAddr;
    if((nwkAddr.contains(VALID_NWKADDR)) == true)
    {
        ui->nwkAddrEdit->setText(tr("Invalid"));
        //ui->parAddrEdit->setText(tr("Invalid"));
        //ui->hwAddrEdit->setText(tr("Invalid"));
        ui->labelPic->setPixmap(pic[0]);
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
        //ui->hwAddrEdit->setText(QByteArray((char *)mac, 8).toHex());
        ui->labelPic->setPixmap(QPixmap());
    }
}

void Ipv6Secure::updateNodeData(char data)
{
        static char lastDat = 0;
    switch(data)
    {
    case 0:
                if(lastDat == 0)
                {
                        ui->labelPic->setPixmap(pic[0]);
                        ui->labelPic->setScaledContents(true);
                        PicTimer->stop();
                }
        break;
    case 1:
        ui->labelPic->setPixmap(pic[1]);
        ui->labelPic->setScaledContents(true);
        PicTimer->start(100);
                break;
    default:
        ui->labelPic->setPixmap(QPixmap());
    }
        lastDat = data;
}

void Ipv6Secure::PicTimeout()
{
    static int stat=1;
    static int orX = 0;

//qDebug()<<"Ipv6Excute::reconnect==== stat:"<<stat<<";funcID:"<<funcID;
    if(stat == 1)
    {
        orX = ui->labelPic->x();
       ui->labelPic->move(ui->labelPic->x()+5,ui->labelPic->y());
       stat++;
    }
    else if(stat < 30)
    {
        ui->labelPic->move(ui->labelPic->x() + 5, ui->labelPic->y());
        stat++;
    }
    else
    {
        ui->labelPic->move(orX,ui->labelPic->y());
        stat = 1;
    }

}

void Ipv6Secure::showEvent(QShowEvent *)
{
    if(wsnSrvUser == NULL)
    {
        wsnSrvUser = ipv6comm_register(wsnSrvIp.toUtf8().constData(),
                    NULL, cbNewFunc, cbNewData, cbNodeGone,
                    NULL, (void *)this);
    }
}

void Ipv6Secure::hideEvent(QHideEvent *)
{
    ipv6comm_unregister(wsnSrvUser);
    wsnSrvUser = NULL;
}

static Ipv6Secure *secure = NULL;
void Ipv6Secure::showOut(const QString &ip, quint8 id)
{
    if(secure == NULL)
        secure = new Ipv6Secure(ip, id);
    else
        secure->reconnect(ip, id);
    secure->show();
}

void Ipv6Secure::cbNewFunc(void *arg, unsigned char *nwkAddr, int funcNum, IPV6COMM_NODE_FUNC *funcList)
{
    Ipv6Secure *This = qobject_cast<Ipv6Secure *>((QObject *)arg);
    if(This == NULL)
        return;
    int i;
    for(i = 0; i < funcNum; i++)
    {
        if((funcList[i].funcCode == DevIRPers) && ((This->funcID == 0xFF) || (This->funcID == funcList[i].funcID)))
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

void Ipv6Secure::cbNewData(void *arg, unsigned char *nwkAddr, int endPoint, int funcCode, int funcID, char *data, int len)
{
    Q_UNUSED(endPoint);Q_UNUSED(len);
    if(funcCode != DevIRPers)
        return;
    Ipv6Secure *This = qobject_cast<Ipv6Secure *>((QObject *)arg);
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
     qDebug()<<"Ipv6Secure::cbNewData==== DevIRPers data:"<<tmpVal;
    emit This->dataChanged((char)data[0]);
}

void Ipv6Secure::cbNodeGone(void *arg, unsigned char *nwkAddr)
{
    Ipv6Secure *This = qobject_cast<Ipv6Secure *>((QObject *)arg);
    if(This == NULL)
        return;
    if( memcmp( nwkAddr, This->curNwkAddr.data(), IPV6_ADDR_LEN) != 0 )
        return;
    This->curNwkAddr = QByteArray::fromHex(VALID_NWKADDR);
    emit This->nodeInfoChanged(This->curNwkAddr);
}
