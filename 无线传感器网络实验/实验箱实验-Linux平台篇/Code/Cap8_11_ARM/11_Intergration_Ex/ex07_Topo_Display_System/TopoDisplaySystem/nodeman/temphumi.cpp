#include "temphumi.h"
#include "ui_temphumi.h"
#include <QTextCodec>
#include <QDebug>
#include <QDesktopWidget>

TempHumi::TempHumi(const QString &ip, quint8 tempId, quint8 hummId, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TempHumi),
    tempFuncID(tempId),
    hummFuncID(hummId),
    wsnSrvUser(NULL),
    curNwkAddr(0xFFFF)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowMinMaxButtonsHint);
    this->setGeometry(QApplication::desktop()->width()/5,40,this->width(),this->height());

    connect(this, SIGNAL(nodeInfoChanged(unsigned short,unsigned short,unsigned char*)), this, SLOT(updateNodeInfo(unsigned short,unsigned short,unsigned char*)));
    connect(this, SIGNAL(gotNewTempData(unsigned short)), this, SLOT(updateTempData(unsigned short)));
    connect(this, SIGNAL(gotNewHumData(unsigned short)), this, SLOT(updateHumData(unsigned short)));

    reconnect(ip, tempFuncID, hummFuncID);
}

TempHumi::~TempHumi()
{
    delete ui;
}

void TempHumi::reconnect(const QString &ip, quint8 tempId, quint8 hummId)
{

    wsnSrvIp = ip;
    tempFuncID = tempId;
    hummFuncID = hummId;
    wsncomm_unregister(wsnSrvUser);
    wsnSrvUser = wsncomm_register(wsnSrvIp.toUtf8().constData(),
                    NULL, cbNewFunc, cbNewData, cbNodeGone,
                    NULL, (void *)this);

    WSNCOMM_NODE *node = wsncomm_getNode_byType(ip.toUtf8().constData(), DevTemp, tempFuncID);
    if(node != NULL)
    {
        curNwkAddr = node->nwkAddr;
        updateNodeInfo(node->nwkAddr, node->parAddr, node->hwAddr);
        wsncomm_delete_node(node);
        char *data = NULL;
        int len = wsncomm_getNodeData_byType(ip.toUtf8().constData(), DevTemp, tempFuncID, &data);
        if(data != NULL)
        {
            updateTempData(*((unsigned short *)data));
            free(data);
        }
        data = NULL;
        len = wsncomm_getNodeData_byType(ip.toUtf8().constData(), DevHumm, hummId, &data);

        if(data != NULL)
        {
            updateHumData(*((unsigned short *)data));
            free(data);
        }
    }
    else
    {
        curNwkAddr = 0xFFFF;
        updateNodeInfo(0xFFFF, 0xFFFF, NULL);
    }
    QString title = QTextCodec::codecForName("UTF-8")->toUnicode(wsncomm_find_nodeTypeString(DevTemp));
    title += " - ";
    if(tempFuncID != 0xFF)
        title += QString::number(tempFuncID);
    else
        title += tr("Any");
    title += " - ";
    if(hummFuncID != 0xFF)
        title += QString::number(hummFuncID);
    else
        title += tr("Any");
    this->setWindowTitle(title);
}

void TempHumi::showEvent(QShowEvent *)
{
    if(wsnSrvUser == NULL)
    {
        wsnSrvUser = wsncomm_register(wsnSrvIp.toUtf8().constData(),
                        NULL, cbNewFunc, cbNewData, cbNodeGone,
                        NULL, (void *)this);
    }
}

void TempHumi::hideEvent(QHideEvent *)
{
    wsncomm_unregister(wsnSrvUser);
    wsnSrvUser = NULL;
}

void TempHumi::updateNodeInfo(unsigned short nwkAddr, unsigned short parAddr, unsigned char *hwAddr)
{
    if(nwkAddr == 0xFFFF)
    {
        ui->nwkAddrEdit->setText(tr("Invalid"));
        ui->parAddrEdit->setText(tr("Invalid"));
        ui->hwAddrEdit->setText(tr("Invalid"));
        ui->tempValueEdit->setText(tr("Invalid"));
        ui->hummValueEdit->setText(tr("Invalid"));
    }
    else
    {
        char tmpString[20];
        sprintf(tmpString, "%04X", nwkAddr);
        ui->nwkAddrEdit->setText(tmpString);
        sprintf(tmpString, "%04X", parAddr);
        ui->parAddrEdit->setText(tmpString);
        ui->hwAddrEdit->setText(QByteArray((char *)hwAddr, 8).toHex());
    }
}

void TempHumi::updateTempData(unsigned short temp)
{
    float v = float(temp) / 100;
    ui->tempValueEdit->setText(QString::number(v));
}

void TempHumi::updateHumData(unsigned short hum)
{
    float v = float(hum) / 100;
    ui->hummValueEdit->setText(QString::number(v) + "%");
}

static TempHumi *tempHumi = NULL;
void TempHumi::showOut(const QString &ip, quint8 tempId, quint8 hummId)
{
    if (tempHumi == NULL)
        tempHumi = new TempHumi(ip, tempId, hummId);
    else
        tempHumi->reconnect(ip, tempId, hummId);
    tempHumi->show();
}

void TempHumi::cbNewFunc(void *arg, unsigned short nwkAddr, int funcNum, WSNCOMM_NODE_FUNC *funcList)
{
    TempHumi *This = qobject_cast<TempHumi *>((QObject *)arg);
    if(This == NULL)
        return;
    int i;
    for(i = 0; i < funcNum; i++)
    {
        if(
            ((funcList[i].funcCode == DevTemp) && ((0xFF == This->tempFuncID) || (funcList[i].funcID == This->tempFuncID)))
          ||((funcList[i].funcCode == DevHumm) && ((0xFF == This->hummFuncID) || (funcList[i].funcID == This->hummFuncID)))
          )
        {
            WSNCOMM_NODE *node = wsncomm_getNode_byAddr(This->wsnSrvIp.toUtf8().constData(), nwkAddr);
            if(node != NULL)
            {
                This->curNwkAddr = nwkAddr;
                emit This->nodeInfoChanged(node->nwkAddr, node->parAddr, node->hwAddr);
                wsncomm_delete_node(node);
            }
        }
    }
}

void TempHumi::cbNewData(void *arg, unsigned short nwkAddr, int endPoint, int funcCode, int funcID, char *data, int len)
{
    TempHumi *This = qobject_cast<TempHumi *>((QObject *)arg);
    if(This == NULL)
        return;
    if(
        ((funcCode == DevTemp) && ((0xFF == This->tempFuncID) || (funcID == This->tempFuncID)))
      ||((funcCode == DevHumm) && ((0xFF == This->hummFuncID) || (funcID == This->hummFuncID)))
      )
    {
        if(This->curNwkAddr == 0xFFFF)
        {
            WSNCOMM_NODE *node = wsncomm_getNode_byAddr(This->wsnSrvIp.toUtf8().constData(), nwkAddr);
            if(node != NULL)
            {
                This->curNwkAddr = nwkAddr;
                emit This->nodeInfoChanged(node->nwkAddr, node->parAddr, node->hwAddr);
                wsncomm_delete_node(node);
            }
            else
                emit This->nodeInfoChanged(0xFFFF, 0xFFFF, NULL);
        }
        unsigned short v = *((unsigned short *)data);
        if(funcCode == DevTemp)
            emit This->gotNewTempData(v);
        else
            emit This->gotNewHumData(v);
    }
}

void TempHumi::cbNodeGone(void *arg, unsigned short nwkAddr)
{
    TempHumi *This = qobject_cast<TempHumi *>((QObject *)arg);
    if(This == NULL)
        return;
    if(nwkAddr != This->curNwkAddr)
        return;
    This->curNwkAddr = 0xFFFF;
    emit This->nodeInfoChanged(0xFFFF, 0xFFFF, NULL);
}
