#include "ID125KControl.h"
#include <qextserialport.h>
#include <QTimer>
#include <QTime>
#include <stdlib.h>
#include <QDebug>

const int ID125KControl::_IDLength = 4;
ID125KControl::ID125KControl(QObject *parent) :
    QObject(parent),
    _commPort(NULL)
{
    _timer = new QTimer(this);
    _timer->setSingleShot(false);
    _timer->setInterval(100);
    connect(_timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
}

ID125KControl::~ID125KControl()
{
    stop();
    delete _timer;
}

bool ID125KControl::isActive() const
{
    return (_commPort != NULL) && (_commPort->isOpen());
}

bool ID125KControl::start(const QString &port)
{
    qDebug()<<"==the Function [start] com port:"<<port;
    if(_commPort != NULL)
        return false;
    _commPort = new QextSerialPort(port, QextSerialPort::EventDriven);
    _commPort->setBaudRate(BAUD19200);
    _commPort->setFlowControl(FLOW_OFF);

    if(_commPort->open(QIODevice::ReadWrite))
    {
        connect(_commPort, SIGNAL(readyRead()), this, SLOT(onCommPortDataReady()));
        _timer->start();
        qDebug()<<"==the Function start com OKKK!";
        return true;
    }
    else
    {
        delete _commPort;
        _commPort = NULL;
        qDebug()<<"==the Function srart com ERRR!";
        return false;
    }
}

void ID125KControl::stop()
{
    if(_timer->isActive())
        _timer->stop();
    if(_commPort != NULL)
    {
        _commPort->disconnect();
        _commPort->close();
        delete _commPort;
        _commPort = NULL;
    }
}

void ID125KControl::onCommPortDataReady()
{
    static QTime lastRecvTime;
    static unsigned long lastDecID = 0;
    // restart the timeout timer
    _timer->start();
    QByteArray bytes;
    int a = _commPort->bytesAvailable();
    bytes.resize(a);
    char *p = bytes.data();
    int len = bytes.size();
    _commPort->read(p, len);
    for(int i = 0; i < len; i++)
    {
        _lastRecvedBytes.append(*p++);
        if(_lastRecvedBytes.size() == _IDLength + 1)
        {
#if 0
            quint8 xorCheck = 0x00;
            for(int j = 0; j < _IDLength; j++)
            {
                xorCheck = (quint8)(xorCheck ^ ((quint8)_lastRecvedBytes[j]));
            }
            if(xorCheck != _lastRecvedBytes[_IDLength])
                ;
#endif
            unsigned long decID = toDecID(_lastRecvedBytes.constData());
            if((lastDecID != decID)
                    || ((abs(lastRecvTime.secsTo(QTime::currentTime())) >= 1)
                        && (decID != 0))
                    )
            {
                emit newCard(decID, _lastRecvedBytes.left(_IDLength));
            }
            lastRecvTime = QTime::currentTime();
            lastDecID = decID;
        }
    }
}

void ID125KControl::onTimeout()
{
    _lastRecvedBytes.clear();
}

unsigned long ID125KControl::toDecID(const char *id)
{
    const quint8 *cardid = (const quint8 *)id;
    return ((cardid[0] << 24) & 0xFF000000)
            | ((cardid[1] << 16) & 0x00FF0000)
            | ((cardid[2] << 8) & 0x0000FF00)
            | (cardid[3] & 0x000000FF);

}
