#include "MicroWaveControl.h"
#include <qextserialport.h>
#include <stdlib.h>

MicroWaveControl::MicroWaveControl(QObject *parent) :
    QObject(parent),
    _commPort(NULL)
{
}

MicroWaveControl::~MicroWaveControl()
{
    stop();
}

bool MicroWaveControl::isActive() const
{
    return (_commPort != NULL) && (_commPort->isOpen());
}

bool MicroWaveControl::start(const QString &port)
{
    if(_commPort != NULL)
        return false;
    _commPort = new QextSerialPort(port, QextSerialPort::EventDriven);
    _commPort->setBaudRate(BAUD9600);
    _commPort->setFlowControl(FLOW_OFF);

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

void MicroWaveControl::stop()
{
    if(_commPort != NULL)
    {
        _commPort->disconnect();
        _commPort->close();
        delete _commPort;
        _commPort = NULL;
    }
}

void MicroWaveControl::onCommPortDataReady()
{
    // restart the timeout timer
    QByteArray bytes;
    int a = _commPort->bytesAvailable();
    bytes.resize(a);
    quint8 *p = (quint8 *)bytes.data();
    int len = bytes.size();
    _commPort->read((char*)p, len);
    for(int i = 0; i < len; i++)
    {
        quint8 ch = *p++;
        if(_lastRecvedBytes.size() < MICROWAVE_HEAD_SIZE)
        {
            if(ch != MICROWAVE_HEAD)
                _lastRecvedBytes.clear();
            else
                _lastRecvedBytes.append((char)ch);
        }
        else
        {
            _lastRecvedBytes.append((char)ch);
            if(_lastRecvedBytes.size() == MICROWAVE_PKG_SIZE)
            {
                const char *p = _lastRecvedBytes.constData();
                p += 5;
                int readerAddr = *p++;
                int cardType = *p & 0x7F;
                bool lowPower = ((*p & 0x80) != 0);
                p++;
                unsigned long decID = toDecID(p);
                emit newCard(readerAddr, cardType, lowPower, decID, QByteArray(p, 4));
                _lastRecvedBytes.clear();
            }
        }
    }
}

unsigned long MicroWaveControl::toDecID(const char *id)
{
    const quint8 *cardid = (const quint8 *)id;
    return ((cardid[0] << 24) & 0xFF000000)
            | ((cardid[1] << 16) & 0x00FF0000)
            | ((cardid[2] << 8) & 0x0000FF00)
            | (cardid[3] & 0x000000FF);

}
