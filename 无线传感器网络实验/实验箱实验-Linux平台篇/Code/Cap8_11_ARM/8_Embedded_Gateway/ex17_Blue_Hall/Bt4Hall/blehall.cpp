#include "blehall.h"
#include "ui_blehall.h"
#include <QTextCodec>
#include <QDebug>
#include <QDesktopWidget>

BleHall::BleHall(const QString &ip, quint8 id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BleHall),
    funcID(id),
    wsnSrvUser(NULL)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowMinMaxButtonsHint);
    this->setGeometry(QApplication::desktop()->width()/5,QApplication::desktop()->height()/2+15
                      ,this->width(),this->height());

    this->timer = new QTimer;
    this->hallAlarmFlag = false;

    pic[0].load(":/pic/secure.png");
    pic[1].load(":/pic/hall.png");
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

BleHall::~BleHall()
{
    delete ui;
}

void BleHall::reconnect(const QString &ip, quint8 id)
{
    wsnSrvIp = ip;
    funcID = id;
    bt4comm_unregister(wsnSrvUser);
    wsnSrvUser = bt4comm_register(wsnSrvIp.toUtf8().constData(),
                    NULL, cbNewFunc, cbNewData, cbNodeGone,
                    NULL, (void *)this);
    int funcType = DevHall;
    BT4COMM_NODE *node = bt4comm_getNode_byType(ip.toUtf8().constData(), funcType, funcID);
    if(node != NULL)
    {

        this->curNwkAddr = QByteArray::fromRawData((const char *)node->nwkAddr, BT_ADDR_LEN);

        updateNodeInfo(this->curNwkAddr);
        char *data = NULL;
        bt4comm_getNodeData_byType(ip.toUtf8().constData(), funcType, funcID, &data);
        if( data != NULL)
            qDebug()<<"BtHall::reconnect==== DevHall data:"<<*((unsigned short *)data);
        else
            qDebug()<<"BtHall::reconnect==== DevHall data err!!";
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
        qDebug()<<"####==BtHall==#### reconnect node is null!";
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

void BleHall::showEvent(QShowEvent *)
{
    if(wsnSrvUser == NULL)
    {
        wsnSrvUser = bt4comm_register(wsnSrvIp.toUtf8().constData(),
                        NULL, cbNewFunc, cbNewData, cbNodeGone,
                        NULL, (void *)this);
    }
}

void BleHall::hideEvent(QHideEvent *)
{
    bt4comm_unregister(wsnSrvUser);
    wsnSrvUser = NULL;
}

void BleHall::updateNodeInfo(QByteArray nwkAddr)
{

    if((nwkAddr.contains(VALID_NWKADDR)) == true)
    {
        ui->nwkAddrEdit->setText(tr("Invalid"));

    }
    else
    {

        ui->nwkAddrEdit->setText(nwkAddr.toHex());
    }
    //qDebug()<<"bleHall::updateNodeInfo==== nwkAddr:"<<hwAddr;
}


void BleHall::updateNodeData(char v)
{
    qDebug()<<"bleHall::updateNodeData==== data:"<<v;
    switch(v)
    {
        case 0:
            {
                if(true == this->hallAlarmFlag)
                {
                    this->hallAlarmFlag = false;
                    timer->stop();
                }
                ui->labelPic->setPixmap(pic[0]);
                ui->labelPic->setScaledContents(true);
                break;
            }
        case 1:
            {
                if(false == this->hallAlarmFlag)
                {
                    this->hallAlarmFlag = true;
                    timer->start(20000);
                    emit gotBleHallAlarm("hall");
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

static BleHall *hall = NULL;
void BleHall::showOut(const QString &ip, quint8 id)
{
    if(hall == NULL)
        hall = new BleHall(ip, id);
    else
        hall->reconnect(ip, id);
    hall->show();
}

void BleHall::cbNewFunc(void *arg, unsigned char *nwkAddr, int funcNum, BT4COMM_NODE_FUNC *funcList)
{
    BleHall *This = qobject_cast<BleHall *>((QObject *)arg);
    uint8   curaddrType = BTCOMM_ADDRTYPE;
    if(This == NULL)
        return;
    int i;
    for(i = 0; i < funcNum; i++)
    {
        if((funcList[i].funcCode == DevHall) && ((This->funcID == 0xFF) || (This->funcID == funcList[i].funcID)))
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

void BleHall::cbNewData(void *arg, unsigned char *nwkAddr, int endPoint, int funcCode, int funcID, char *data, int len)
{
    Q_UNUSED(endPoint);Q_UNUSED(len);
    uint8   curaddrType = BTCOMM_ADDRTYPE;


    if(funcCode != DevHall)
        return;
    BleHall *This = qobject_cast<BleHall *>((QObject *)arg);
    if(This == NULL)
        return;

    if((This->funcID != 0xFF) && (funcID != This->funcID))
        return;
    unsigned char validAddr[BT_ADDR_LEN];
    memset(validAddr, 0xFF, sizeof(validAddr));

    qDebug()<<"bleHall::cbNewData==== funcCode:"<<funcCode<<";funcID:"<<funcID;
    if(memcmp(This->curNwkAddr.data(), validAddr, sizeof(validAddr)) == 0)
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
    emit This->gotNewNodeData(data[0]);
}

void BleHall::cbNodeGone(void *arg, unsigned char *nwkAddr)
{
    BleHall *This = qobject_cast<BleHall *>((QObject *)arg);
    if(This == NULL)
        return;
    if( memcmp( nwkAddr, This->curNwkAddr.data(), BT_ADDR_LEN) != 0 )
        return;
    This->curNwkAddr = QByteArray::fromHex(VALID_NWKADDR);
    emit This->nodeInfoChanged(This->curNwkAddr);
}

void BleHall::timeOut(void)
{
    if(true == this->hallAlarmFlag)
    {
        emit gotBleHallAlarm("hall");
    }
}
