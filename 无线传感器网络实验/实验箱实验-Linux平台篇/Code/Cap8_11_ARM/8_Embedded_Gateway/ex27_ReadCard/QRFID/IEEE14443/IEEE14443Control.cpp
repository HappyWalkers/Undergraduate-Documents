#include "IEEE14443Control.h"
#include "IEEE14443Package.h"
#include <qextserialport.h>
#include <QTimer>
#include <QMessageBox>
#include <QScrollBar>
#include <QDebug>

IEEE14443Control::IEEE14443Control(QObject *parent) :
    QObject(parent),
    commPort(NULL),
    recvStatus(0),
    lastOperation(Idle),
    lastBlock(-1),
    walletMoney(0)
{
    connect(this, SIGNAL(recvPackage(QByteArray)), this, SLOT(onRecvedPackage(QByteArray)));

	commTimer = new QTimer(this);
    commTimer->setInterval(2000);
	commTimer->setSingleShot(true);
	connect(commTimer, SIGNAL(timeout()), this, SLOT(onCommTimeOut()));
}

IEEE14443Control::~IEEE14443Control()
{
    delete commTimer;
}

bool IEEE14443Control::isActive() const
{
    return ((commPort != NULL) && (commPort->isOpen()));
}

bool IEEE14443Control::start(const QString &port)
{
    if(commPort != NULL)
        return false;
    commPort = new QextSerialPort(port,  QextSerialPort::EventDriven);
    commPort->setBaudRate(BAUD19200);
    commPort->setFlowControl(FLOW_OFF);
    commPort->setParity(PAR_NONE);
    commPort->setDataBits(DATA_8);
    commPort->setStopBits(STOP_1);

	if (commPort->open(QIODevice::ReadWrite) == true)
	{
        connect(commPort, SIGNAL(readyRead()), this, SLOT(onPortDataReady()));
        return true;
    }
	else
	{
        qDebug() << "device failed to open:" << commPort->errorString();
        delete commPort;
        commPort = NULL;
        return false;
    }
}

void IEEE14443Control::stop()
{
	lastOperation = Idle;
	commTimer->stop();
	if(commPort != NULL)
    {
        commPort->close();
        delete commPort;
    }
    commPort = NULL;
}

bool IEEE14443Control::getCardId()
{
    if((commPort == NULL) || (!commPort->isOpen()))
        return false;//QMessageBox::information(this, tr("Tip"), tr("Don't forget open serial port"));
    else if(lastOperation == Idle)
    {
        lastOperation = GetCardId;
        process_searchCard();
        return true;
    }
    return false;
}

bool IEEE14443Control::readCard(int block)
{
    if((commPort == NULL) || (!commPort->isOpen()))
        return false;//QMessageBox::information(this, tr("Tip"), tr("Don't forget open serial port"));
    else if(lastOperation == Idle)
    {
        lastOperation = ReadCard;
        lastBlock = block;
        process_searchCard();
        return true;
    }
    return false;
}

bool IEEE14443Control::writeCard(int block, const QByteArray &data)
{
    if(data.size() != 16)
        return false;
    if((commPort == NULL) || (!commPort->isOpen()))
        return false;//QMessageBox::information(this, tr("Tip"), tr("Don't forget open serial port"));
    else if(lastOperation == Idle)
    {
        lastOperation = WriteCard;
        lastBlock = block;
        lastCardData = data;
        process_searchCard();
        return true;
    }
    return false;
}

void IEEE14443Control::closeAnti()
{
    if((commPort == NULL) || (!commPort->isOpen()))
        return;
    else if(lastOperation == Idle)
    {
        lastOperation = AntiControl;
        process_antiControl(0);
    }
}

void IEEE14443Control::openAnti()
{
    if((commPort == NULL) || (!commPort->isOpen()))
        return;
    else if(lastOperation == Idle)
    {
        lastOperation = AntiControl;
        process_antiControl(1);
    }
}

bool IEEE14443Control::walletInit(int block, int money)
{
    if((commPort == NULL) || (!commPort->isOpen()))
        return false;//QMessageBox::information(this, tr("Tip"), tr("Don't forget open serial port"));
    else if(lastOperation == Idle)
    {
        lastOperation = WalletInit;
        lastBlock = block;
        walletMoney = money;
        process_searchCard();
        return true;
    }
    return false;
}

bool IEEE14443Control::walletGet(int block)
{
    if((commPort == NULL) || (!commPort->isOpen()))
        return false;//QMessageBox::information(this, tr("Tip"), tr("Don't forget open serial port"));
    else if(lastOperation == Idle)
    {
        lastOperation = WalletGet;
        lastBlock = block;
        process_searchCard();
        return true;
    }
    return false;
}

bool IEEE14443Control::walletCharge(int block, int money)
{
    if((commPort == NULL) || (!commPort->isOpen()))
        return false;//QMessageBox::information(this, tr("Tip"), tr("Don't forget open serial port"));
    else if(lastOperation == Idle)
    {
        lastOperation = WalletCharge;
        lastBlock = block;
        walletMoney = money;
        process_searchCard();
        return true;
    }
    return false;
}

bool IEEE14443Control::walletRecharge(int block, int money)
{
    if((commPort == NULL) || (!commPort->isOpen()))
        return false;//QMessageBox::information(this, tr("Tip"), tr("Don't forget open serial port"));
    else if(lastOperation == Idle)
    {
        lastOperation = WalletRecharge;
        lastBlock = block;
        walletMoney = money;
        process_searchCard();
        return true;
    }
    return false;
}

/************************************************************************/
bool IEEE14443Control::sendData(const QByteArray &data)
{
    if(commPort)
    {
        commPort->write(IEEE14443Package(data).toRawPackage());
		commTimer->start();
    }
    return true;
}

// 串口接收数据函数, 通常不需要修改
void IEEE14443Control::onPortDataReady()
{
    QByteArray bytes;
    int a = commPort->bytesAvailable();
    bytes.resize(a);
    char *p = bytes.data();
    int len = bytes.size();
    commPort->read(p, len);
    while(len--)
    {
        switch(recvStatus)
        {
        case 0:// recv sync code
            if(*p == 0x02)
            {
                recvStatus = 1;
                lastRecvPackage.clear();
                lastRecvPackage.append(*p);
            }
            p++;
            break;
        case 1:// normal recv
            if(*p == 0x10)
                recvStatus = 2;
            else if(*p == 0x03)
            {
                // recved a end code
                lastRecvPackage.append(*p);
                emit recvPackage(lastRecvPackage);
                lastRecvPackage.clear();
                recvStatus = 0;
            }
            else // just append the data
                lastRecvPackage.append(*p);
            p++;
            break;
        case 2:// recved a escape code last time, so just append data to the package
            lastRecvPackage.append(*p++);
            recvStatus = 1;
            break;
        }
    }
}

// 接收到完整数据包的处理函数
void IEEE14443Control::onRecvedPackage(QByteArray pkg)
{
    IEEE14443Package p(pkg);
    QByteArray d = p.data();
    int status = d.at(0);
    d = d.mid(1);
    //QString resultTipText;
	commTimer->stop();
    enum { NoNeedEmitSignals, EmitError, EmitFoundCard, EmitReaded, EmitWritten, EmitWalletInit, EmitWalletGet, EmitWalletCharge, EmitWalletRecharge };
    int emitStatus = NoNeedEmitSignals;
    int op = lastOperation;
    QString result;
    switch(p.command())
    {
    case IEEE14443Package::AntiCtrl:
        //resultTipText = tr("Anti ctrl over %1").arg(status);
        qDebug()<<"AntiCtrl"<<status;
        status = 1;     // operation is done
		break;
    case IEEE14443Package::SearchCard:
        // response for process_searchCard()
        //resultTipText = tr("Search Card ");
        if(status == 0)
		{
            //resultTipText += tr("Succeed");
            process_getId();
		}
        else
        {
            result = tr("Search Card Failed");
            emitStatus = EmitError;
        }
        break;
    case IEEE14443Package::AntiColl:
        // response for process_getId()
        //resultTipText = tr("AntiColl ");
        if(status == 0)
        {
            lastCardId = d;
            if(lastOperation != GetCardId)
                process_selCard();
            else
            {
//                emitStatus = EmitFoundCard;
                status = 1;
            }
            emitStatus = EmitFoundCard;
        }
        else
        {
            result = tr("AntiColl Failed");
            emitStatus = EmitError;
        }
        break;
    case IEEE14443Package::SelectCard:
        // response for process_selCard()
        if(status == 0)
        {
            process_authCheck();
        }
        else
        {
            result = tr("Select Card Failed");
            emitStatus = EmitError;
        }
        break;
    case IEEE14443Package::Authentication:
        // response for process_authCheck()
        if(status == 0)
		{
            switch(lastOperation)
            {
            case ReadCard:
                process_read();
                break;
            case WriteCard:
                process_write();
                break;
            case WalletInit:
                process_walletInit();
                break;
            case WalletGet:
                process_walletGet();
                break;
            case WalletCharge:
                process_walletCharge();
                break;
            case WalletRecharge:
                process_walletRecharge();
                break;
            default:
                status = 1;
                break;
            }
		}
        else
        {
            result = tr("Authentication Failed");
            emitStatus = EmitError;
        }
        break;
    case IEEE14443Package::ReadCard:
        // response for process_read()
        if(status == 0)
        {
            // 读卡指令的响应 可以获得卡内数据
            // 读取正常
            lastCardData = d;
            emitStatus = EmitReaded;
        }
        else
        {
            result = tr("Read Failed");
            emitStatus = EmitError;
        }
		status = 1;		// operation is done, mark the status invalid to go back to Idle
        break;
    case IEEE14443Package::WriteCard:
        // response for process_write()
        if(status == 0)
            emitStatus = EmitWritten;
        else
        {
            result = tr("Write Failed");
            emitStatus = EmitError;
        }
        status = 1;		// operation is done, mark the status invalid to go back to Idle
		break;
    case IEEE14443Package::InitWallet:
        if(status == 0)
            emitStatus = EmitWalletInit;
        else
        {
            result = tr("Wallet init failed");
            emitStatus = EmitError;
        }
        status = 1;
        break;
    case IEEE14443Package::GetWallet:
        if(status == 0)
        {
            memcpy(&walletMoney, d.constData(), 4);
            emitStatus = EmitWalletGet;
        }
        else
        {
            result = tr("Wallet get failed");
            emitStatus = EmitError;
        }
        status = 1;
        break;
    case IEEE14443Package::ChargeWallet:
        if(status == 0)
            emitStatus = EmitWalletCharge;
        else
        {
            result = tr("Wallet Charge failed");
            emitStatus = EmitError;
        }
        status = 1;
        break;
    case IEEE14443Package::RechargeWallet:
        if(status == 0)
            emitStatus = EmitWalletRecharge;
        else
        {
            result = tr("Wallet Recharge failed");
            emitStatus = EmitError;
        }
        status = 1;
        break;
    default:
        emitStatus = EmitError;
        result = tr("unknown package!!!");
        status = 1;
        break;
    }
	if(status != 0)
		lastOperation = Idle;
    switch(emitStatus)
    {
    case EmitError: emit error(op, result); break;
    case EmitFoundCard: emit foundCard(lastCardId); break;
    case EmitReaded: emit dataReaded(lastBlock, lastCardData); break;
    case EmitWritten: emit dataWritten(lastBlock); break;
    case EmitWalletInit: emit walletInitialised(lastBlock); break;
    case EmitWalletGet: emit walletGetted(lastBlock, walletMoney); break;
    case EmitWalletCharge: emit walletCharged(lastBlock); break;
    case EmitWalletRecharge: emit walletRecharged(lastBlock); break;
    }
}

void IEEE14443Control::onCommTimeOut()
{
    qDebug()<<"onCommTimeout";
	commTimer->stop();
    int op = lastOperation;
    lastOperation = Idle;
    emit error(op, tr("Operation Timeout"));
}

/************************************************************************/
void IEEE14443Control::process_antiControl(int on)
{
    lastSendPackage = IEEE14443Package(0, IEEE14443Package::AntiCtrl, on).toPurePackage();
	sendData(lastSendPackage);
}

void IEEE14443Control::process_searchCard()
{
    lastSendPackage = IEEE14443Package(0, IEEE14443Package::SearchCard, 0x52).toPurePackage();
	sendData(lastSendPackage);
}

void IEEE14443Control::process_getId()
{
    lastSendPackage = IEEE14443Package(0, IEEE14443Package::AntiColl, 0x04).toPurePackage();
    sendData(lastSendPackage);
}

void IEEE14443Control::process_selCard()
{
    IEEE14443Package pkg(0, IEEE14443Package::SelectCard, lastCardId);
    lastSendPackage = pkg.toPurePackage();
    sendData(lastSendPackage);
}

void IEEE14443Control::process_authCheck()
{
    QByteArray authInfo;
    authInfo.append(0x60);      // Always use Type A
    // TODO:
    authInfo.append((char)lastBlock);
    authInfo.append(QByteArray(6, 0xFF));

    IEEE14443Package pkg(0, IEEE14443Package::Authentication, authInfo);
    lastSendPackage = pkg.toPurePackage();
    sendData(lastSendPackage);
}

void IEEE14443Control::process_read()
{
    IEEE14443Package pkg(0, IEEE14443Package::ReadCard, (char)lastBlock);
    lastSendPackage = pkg.toPurePackage();
    sendData(lastSendPackage);
}

void IEEE14443Control::process_write()
{
	QByteArray writeInfo;
    writeInfo.append((char)lastBlock);
    // TODO:
    writeInfo.append(lastCardData);
    IEEE14443Package pkg(0, IEEE14443Package::WriteCard, writeInfo);
	lastSendPackage = pkg.toPurePackage();
	sendData(lastSendPackage);
}

void IEEE14443Control::process_walletInit()
{
    QByteArray data;
    data.append((char)lastBlock);
    data.append((char *)&walletMoney, 4);
    IEEE14443Package pkg(0, IEEE14443Package::InitWallet, data);
    lastSendPackage = pkg.toPurePackage();
    sendData(lastSendPackage);
}

void IEEE14443Control::process_walletGet()
{
    IEEE14443Package pkg(0, IEEE14443Package::GetWallet, (char)lastBlock);
    lastSendPackage = pkg.toPurePackage();
    sendData(lastSendPackage);
}

void IEEE14443Control::process_walletCharge()
{
    QByteArray data;
    data.append((char)lastBlock);
    data.append((char *)&walletMoney, 4);
    IEEE14443Package pkg(0, IEEE14443Package::ChargeWallet, data);
    lastSendPackage = pkg.toPurePackage();
    sendData(lastSendPackage);
}

void IEEE14443Control::process_walletRecharge()
{
    QByteArray data;
    data.append((char)lastBlock);
    data.append((char *)&walletMoney, 4);
    IEEE14443Package pkg(0, IEEE14443Package::RechargeWallet, data);
    lastSendPackage = pkg.toPurePackage();
    sendData(lastSendPackage);
}
