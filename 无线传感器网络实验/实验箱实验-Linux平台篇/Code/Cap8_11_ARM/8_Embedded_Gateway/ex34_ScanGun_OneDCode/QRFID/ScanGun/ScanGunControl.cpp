#include "ScanGunControl.h"
#include <qextserialport.h>
#include <QTimer>
#include <QTime>
#include <stdlib.h>

ScanGunControl::ScanGunControl(QObject *parent) :
    QObject(parent),
    _commPort(NULL)
{
    _timer = new QTimer(this);
    _timer->setSingleShot(true);
    _timer->setInterval(10);
    connect(_timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
}

ScanGunControl::~ScanGunControl()
{
    stop();
    delete _timer;
}

bool ScanGunControl::isActive() const
{
    return (_commPort != NULL) && (_commPort->isOpen());
}

bool ScanGunControl::start(const QString &port)
{
    if(_commPort != NULL)
        return false;

    _commPort = new QextSerialPort(port, QextSerialPort::EventDriven);
    _commPort->setBaudRate(BAUD9600);
    _commPort->setFlowControl(FLOW_OFF);
    _commPort->setParity(PAR_NONE);
    _commPort->setDataBits(DATA_8);
    _commPort->setStopBits(STOP_1);

    if(_commPort->open(QIODevice::ReadWrite))
    {
        connect(_commPort, SIGNAL(readyRead()), this, SLOT(onCommPortDataReady()));
        return true;
    }
    else
    {
        delete _commPort;
        _commPort = NULL;
        return false;
    }
}

void ScanGunControl::stop()
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

void ScanGunControl::onCommPortDataReady()
{
    QByteArray bytes;
    int a = _commPort->bytesAvailable();
    bytes.resize(a);
    char *p = bytes.data();
    int len = bytes.size();
    _commPort->read(p, len);

    bool hasEnter = false;
    for(int i = 0; i < len; i++)
    {
        char ch = *p++;
        if(ch == '\n')
        {
            reportScanResult();
            hasEnter = true;
        }
        else
            _lastRecvedBytes.append(ch);
    }
    if(!hasEnter)
        _timer->start();
}

void ScanGunControl::onTimeout()
{
    reportScanResult();
}

void ScanGunControl::reportScanResult()
{
    _lastRecvedBytes = _lastRecvedBytes.trimmed();
    if(!_lastRecvedBytes.isEmpty())
    {
        emit scanResult(_lastRecvedBytes);
        _lastRecvedBytes.clear();
    }
}
