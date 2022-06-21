#include "RLM100Control.h"
#include "RLM100Package.h"
#include <qextserialport.h>
#include <QTimer>
#include <QTime>
#include <QEventLoop>
#include <QDebug>

RLM100Control::RLM100Control(QObject *parent) :
	QObject(parent),
    commPort(NULL)
{
	timer = new QTimer(this);
    timer->setInterval(2000);
	timer->setSingleShot(true);
	connect(timer, SIGNAL(timeout()), this, SLOT(onOpTimeout()));

    _syncHelper = new QEventLoop(this);
    syncTimer = new QTimer(this);
    syncTimer->setInterval(5);
    syncTimer->setSingleShot(true);
    connect(syncTimer, SIGNAL(timeout()), _syncHelper, SLOT(quit()));
}

RLM100Control::~RLM100Control()
{
	if(commPort != NULL)
		stop();
	delete timer;
    delete syncTimer;
    delete _syncHelper;
}

/**
 * @brief RLM100Control::start
 * @param port 串口设备文件路径
 *
 * 打开串口设备
 */
void RLM100Control::start(const QString &port)
{
	if(commPort != NULL)
		return;
    commPort = new QextSerialPort(port,  QextSerialPort::EventDriven);
    commPort->setBaudRate(BAUD57600);
	commPort->setFlowControl(FLOW_OFF);
	commPort->setParity(PAR_NONE);
	commPort->setDataBits(DATA_8);
	commPort->setStopBits(STOP_1);

	if (commPort->open(QIODevice::ReadWrite) == true) {
		connect(commPort, SIGNAL(readyRead()), this, SLOT(onPortDataReady()));
        //readSetting();
	}
	else {
		qDebug() << "device failed to open:" << commPort->errorString();
		delete commPort;
		commPort = NULL;
	}
}

/**
 * @brief RLM100Control::stop
 *
 * 关闭串口
 */
void RLM100Control::stop()
{
    if(_syncHelper->isRunning())
        _syncHelper->exit();
	lastRecvedPackage.clear();
	if(commPort != NULL)
	{
        commPort->disconnect();
		commPort->close();
		commPort->deleteLater();
	}
	commPort = NULL;
}

/**
 * @brief RLM100Control::isActive
 * @return true： 串口已经打开<br />
 * false: 串口未打开
 *
 * 判断串口是否已经打开
 */
bool RLM100Control::isActive() const
{
    return ((commPort != NULL) && commPort->isOpen());
}

/**
 * @brief RLM100Control::isBusy
 * @return true: 系统忙,上一条命令还没执行完
 * false: 系统不忙,可以执行下一条命令
 */
bool RLM100Control::isBusy() const
{
    return ((_syncHelper != NULL) && _syncHelper->isRunning());
}

// 串口接收数据函数, 通常不需要修撍
void RLM100Control::onPortDataReady()
{
    static QTime lastRecvTim;
    qDebug()<<"======= the data is =======";
    bool escapeFlag = false;
    QByteArray bytes;
    int a = commPort->bytesAvailable();
    bytes.resize(a);
    quint8 *p = (quint8 *)bytes.data();
    int len = bytes.size();
    commPort->read((char*)p, len);

    if(abs(QTime::currentTime().msecsTo(lastRecvTim)) > 80)
        lastRecvedPackage.clear();
    lastRecvTim = QTime::currentTime();

    while(len--)
    {
        if(lastRecvedPackage.isEmpty() && (*p != RLM100Package::StartOfFrame))
            continue;
        if(escapeFlag)
        {
            lastRecvedPackage.append(*p);
            p++;
            escapeFlag = false;
            continue;
        }
        if((escapeFlag == false) && (*p == RLM100Package::EscapeChar))
        {
            p++;
            escapeFlag = true;
            continue;
        }
        lastRecvedPackage.append(*p);
        if(*p == RLM100Package::EndOfFrame)
        {
            qDebug()<<__PRETTY_FUNCTION__<<lastRecvedPackage.toHex();
            timer->stop();
            RLM100Package pkg(lastRecvedPackage);
            onPackageReadyHook(pkg);
            lastRecvedPackage.clear();
            syncTimer->start();
        }
        p++;
    }
}

void RLM100Control::onPackageReadyHook(const RLM100Package &pkg)
{
    if(pkg.isValid())
    {
        _respStatus = pkg.responseStatus();
        _respData = pkg.responseData();
        switch(pkg.command())
        {
        case RLM100Package::Inventory:
        case RLM100Package::InventoryAnti:
            if(_respStatus == 0x00)
            {
#if 1
                emit newEPC(_respData);
#else
                QByteArray epc = RLM100Package::uii2epc(_respData);
                if(!epc.isEmpty())
                    emit newEPC(epc);
#endif
            }
            break;
        }
    }
    else
    {
        _respStatus = -1;
        _respData.clear();
    }
}

void RLM100Control::onOpTimeout()
{
    qDebug()<<__PRETTY_FUNCTION__;
    _respStatus = -1;
    syncTimer->start();
    emit timeout();
}

void RLM100Control::writeCommand(const RLM100Package &pkg)
{
    qDebug()<<__PRETTY_FUNCTION__<<pkg.toRawPackage().toHex();
    commPort->write(pkg.toRawPackage());
    timer->start();
    _syncHelper->exec();
}

/**************************************************************
 *
 *
 *************************************************************/
bool RLM100Control::getStatus()
{
    if(isBusy())
        return false;
    writeCommand(RLM100Package(RLM100Package::GetStatus));
    return (_respStatus == 0);
}

int RLM100Control::getPower()
{
    if(isBusy())
        return -1;
    writeCommand(RLM100Package(RLM100Package::GetPower));
    if(_respData.isEmpty())
        return -1;
    return _respData.at(0) & 0x7F;
}

bool RLM100Control::setPower(int power)
{
    if(isBusy())
        return false;
    QByteArray d;
    d.append(1);
    d.append(char(power&0x7F));
    writeCommand(RLM100Package(RLM100Package::SetPower, d));
    return (_respStatus == 0);
}
#if 0
bool RLM100Control::readReg(quint16 startAddr, quint16 len, QByteArray &regs)
{
    regs.clear();
    if(isBusy())
        return false;
    QByteArray d;
    d.append(char(startAddr >> 8));
    d.append(char(startAddr & 0xFF));
    d.append(char(len >> 8));
    d.append(char(len & 0xFF));
    writeCommand(RLM100Package(RLM100Package::ReadReg, d));
    if(_respStatus == 0)
        regs = _respData;
    return (_respStatus == 0);
}

bool RLM100Control::writeReg(quint16 startAddr, const QByteArray &regs)
{
    if(isBusy())
        return false;
    quint16 len = regs.length();
    QByteArray d;
    d.append(char(startAddr >> 8));
    d.append(char(startAddr & 0xFF));
    d.append(char(len >> 8));
    d.append(char(len & 0xFF));
    d.append(regs);
    writeCommand(RLM100Package(RLM100Package::WriteReg, d));
    return (_respStatus == 0);
}

bool RLM100Control::resetReg()
{
    if(isBusy())
        return false;
    writeCommand(RLM100Package(RLM100Package::ResetReg));
    return (_respStatus == 0);
}

bool RLM100Control::saveReg()
{
    if(isBusy())
        return false;
    writeCommand(RLM100Package(RLM100Package::SaveReg));
    return (_respStatus == 0);
}
#endif
bool RLM100Control::getVersion(QByteArray &hwSerial, QByteArray &swVersion)
{
    hwSerial.clear();
    swVersion.clear();
    if(isBusy())
        return false;
    writeCommand(RLM100Package(RLM100Package::GetVersion));
    if(_respStatus == 0)
    {
        hwSerial = _respData.left(6);
        swVersion = _respData.right(3);
        return true;
    }
    return false;
}
#if 0
bool RLM100Control::getUID(QByteArray &uid)
{
    uid.clear();
    if(isBusy())
        return false;
    writeCommand(RLM100Package(RLM100Package::ReadUID));
    if(_respStatus == 0)
        uid = _respData;
    return (_respStatus == 0);
}
#endif
bool RLM100Control::sleep()
{
    if(isBusy())
        return false;
    writeCommand(RLM100Package(RLM100Package::EnterSleep));
    return (_respStatus == 0);
}

bool RLM100Control::stopOperation()
{
    if(isBusy())
        return false;
    writeCommand(RLM100Package(RLM100Package::StopGet));
    return (_respStatus == 0);
}

bool RLM100Control::singleScan(QByteArray &uii)
{
    uii.clear();
    if(isBusy())
        return false;
    writeCommand(RLM100Package(RLM100Package::InventorySingle));
    if(_respStatus == 0)
#if 1
        uii = _respData;
#else
        epc = RLM100Package::uii2epc(_respData);
#endif
    return ((_respStatus & 0x80) == 0);
}

bool RLM100Control::startSingleScanLoop()
{
    if(isBusy())
        return false;
    writeCommand(RLM100Package(RLM100Package::Inventory));
    return (_respStatus == 0x01);
}

bool RLM100Control::startMultiScanLoop(int q)
{
    if((q < 0) || (q > 15))
        q = 3;
    if(isBusy())
        return false;
    writeCommand(
                RLM100Package(RLM100Package::InventoryAnti,
                              QByteArray(1, char(q)))
                );
    return (_respStatus == 0x01);
}

bool RLM100Control::readCard(QByteArray &outData,
                             const QByteArray &uii,
                             Sections section,
                             uint startAddress, int len,
                             const QByteArray &apwd)
{
    outData.clear();
    if(isBusy())
        return false;
    QByteArray d;
    d.append(apwd);
    d.append(char(section));
    d.append(char(startAddress));
    d.append(char(len));
#if 1
    d.append(uii);
#else
    d.append(RLM100Package::epc2uii(epc));
#endif
    writeCommand(RLM100Package(RLM100Package::ReadData, d));
    if(_respStatus == 0x00)
    {
        if(len == 0)
        {
            outData = _respData.mid(2);
        }
        else
        {
            outData = _respData;
        }
    }
    return (_respStatus == 0x00);
}

bool RLM100Control::read(QByteArray &outData, QByteArray &outUII,
                             Sections section,
                             uint startAddress, int len,
                             const QByteArray &apwd)
{
    outData.clear();
    outUII.clear();
    if(isBusy())
        return false;
    QByteArray d;
    d.append(apwd);
    d.append(char(section));
    d.append(char(startAddress));
    d.append(char(len));
    writeCommand(RLM100Package(RLM100Package::SingleReadData, d));
    if(_respStatus == 0x00)
    {
        if(len == 0)
        {
            len = _respData[0];
            len <<= 8;
            len |= ((quint8)_respData[1]);
            outData = _respData.mid(2, len);
#if 1
            outUII = _respData.mid(2 + len);
#else
            outEPC = RLM100Package::uii2epc(_respData.mid(2 + len));
#endif
        }
        else
        {
            outData = _respData.left(len * 2);
#if 1
            outUII = _respData.mid(len * 2);
#else
            outEPC = RLM100Package::uii2epc(_respData.mid(len * 2));
#endif
        }
    }
    return (_respStatus == 0x00);
}

bool RLM100Control::writeCard1Word(const QByteArray &data,
                                   const QByteArray &uii,
                                   Sections section,
                                   uint startAddress, const QByteArray &apwd)
{
    if(isBusy())
        return false;
    QByteArray d;
    d.append(apwd);
    d.append(char(section));
    d.append(char(startAddress));
    d.append(1);
    d.append(data.left(2));
#if 1
    d.append(uii);
#else
    d.append(RLM100Package::epc2uii(epc));
#endif
    writeCommand(RLM100Package(RLM100Package::WriteData, d));
    return (_respStatus == 0x00);
}

bool RLM100Control::write1Word(const QByteArray &data,
                               QByteArray &outUII,
                               Sections section,
                               uint startAddress, const QByteArray &apwd)
{
    outUII.clear();
    if(isBusy())
        return false;
    QByteArray d;
    d.append(apwd);
    d.append(char(section));
    d.append(char(startAddress));
    d.append(1);
    d.append(data.left(2));
    writeCommand(RLM100Package(RLM100Package::SingleWriteData, d));
    if(_respStatus == 0x00)
    {
#if 1
        outUII = _respData;
#else
        outEPC = RLM100Package::uii2epc(_respData);
#endif
    }
    return (_respStatus == 0x00);
}

bool RLM100Control::writeCard(const QByteArray &data,
                              const QByteArray &uii,
                              Sections section,
                              uint startAddress, const QByteArray &apwd)
{
    int len = data.length() & ~0x01;
    if(data.isEmpty())
        return false;
    if(isBusy())
        return false;
    QByteArray d;
    d.append(apwd);
    d.append(char(section));
    d.append(char(startAddress));
    d.append(char(len / 2));
    d.append(data.left(len));
#if 1
    d.append(uii);
#else
    d.append(RLM100Package::epc2uii(epc));
#endif
    writeCommand(RLM100Package(RLM100Package::BlockWriteData, d));
    return (_respStatus == 0x00);
}

bool RLM100Control::write(const QByteArray &data,
                          QByteArray &outUII,
                          Sections section,
                          uint startAddress, const QByteArray &apwd)
{
    outUII.clear();
    int len = data.length() & ~0x01;
    if(data.isEmpty())
        return false;
    if(isBusy())
        return false;
    QByteArray d;
    d.append(apwd);
    d.append(char(section));
    d.append(char(startAddress));
    d.append(char(len / 2));
    d.append(data.left(len));
    writeCommand(RLM100Package(RLM100Package::SingleBlockWriteData, d));
    if(_respStatus == 0x00)
    {
#if 1
        outUII = _respData;
#else
        outEPC = RLM100Package::uii2epc(_respData);
#endif
    }
    return (_respStatus == 0x00);
}

bool RLM100Control::eraseCard(const QByteArray &uii,
                              Sections section,
                              uint startAddress,
                              int len, const QByteArray &apwd)
{
    if(isBusy())
        return false;
    QByteArray d;
    d.append(apwd);
    d.append(char(section));
    d.append(char(startAddress));
    d.append(char(len / 2));
#if 1
    d.append(uii);
#else
    d.append(RLM100Package::epc2uii(epc));
#endif
    writeCommand(RLM100Package(RLM100Package::EraseData, d));
    return (_respStatus == 0x00);
}

bool RLM100Control::erase(QByteArray &outUII,
                          Sections section,
                          uint startAddress,
                          int len, const QByteArray &apwd)
{
    outUII.clear();
    if(isBusy())
        return false;
    QByteArray d;
    d.append(apwd);
    d.append(char(section));
    d.append(char(startAddress));
    d.append(char(len / 2));
    writeCommand(RLM100Package(RLM100Package::SingleEraseData, d));
    if(_respStatus == 0x00)
    {
#if 1
        outUII = _respData;
#else
        outEPC = RLM100Package::uii2epc(_respData);
#endif
    }
    return (_respStatus == 0x00);
}
