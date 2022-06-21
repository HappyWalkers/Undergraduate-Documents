#include "RFIDChannelMan.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#ifndef _WIN32
#include <sys/ioctl.h>
#endif
#include <QTimer>

int RFIDChannelMan::_ioFile1 = -1;
int RFIDChannelMan::_ioFile2 = -1;
//int RFIDChannelMan::_beepFile = -1;
RFIDChannelMan *RFIDChannelMan::_instance = NULL;

RFIDChannelMan::RFIDChannelMan(QObject *parent)
    : QObject(parent)
{
    _instance = this;
    _timer = new QTimer(this);
    _timer->setSingleShot(true);
    connect(_timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
    initPort();
}

RFIDChannelMan::~RFIDChannelMan()
{
    _instance = NULL;
    delete _timer;
}

void RFIDChannelMan::onTimeout()
{
//    selectBeep(ChannelInvalid);
}

int RFIDChannelMan::channel()
{
    int ch = 0;
    if(data(0))
        ch |= 0x01;
    if(data(1))
        ch |= 0x02;
    if(data(2))
        ch |= 0x04;
    return ch;
}

void RFIDChannelMan::setChannel(int channel)
{
    channel &= 0x07;
    setData(0, !!(channel & 0x01));
    setData(1, !!(channel & 0x02));
    setData(2, !!(channel & 0x04));
}

//void RFIDChannelMan::selectBeep(int channel, int ms)
//{
//    int bit = -1;
//    switch(channel)
//    {
//    case Channel125K:
//        bit = 2;
//        break;
//    case ChannelIEEE14443:
//        bit = 1;
//        break;
//    case ChannelMicrowave:
//        bit = 0;
//        break;
//    }
//    setBeepData(0, bit == 0);
//    setBeepData(1, bit == 1);
//    setBeepData(2, bit == 2);
//    if(bit != -1)
//        _instance->_timer->start(ms);
//    else
//        _instance->_timer->stop();
//}

void RFIDChannelMan::openPort()
{
    if(_ioFile1 < 0)
        _ioFile1 = open("/dev/gpJ4", O_RDWR);
    if(_ioFile2 < 0)
        _ioFile2 = open("/dev/gpJ4", O_RDWR);
//    if(_beepFile < 0)
//        _beepFile = open("/dev/gpJ0", O_RDWR);
}

void RFIDChannelMan::closePort()
{
    if(_ioFile1 >= 0)
        ::close(_ioFile1);
    if(_ioFile2 >= 0)
        ::close(_ioFile2);
    _ioFile1 = -1;
    _ioFile2 = -1;
}

void RFIDChannelMan::setDir(int bit, bool out)
{
    switch(bit)
    {
//     case 0:            // GPJ2_7//songwei
     case 0:            // GPJ4_0
#ifndef WIN32
//         ::ioctl(ioFile1, type & 0x01, 7);//songwei
        ::ioctl(_ioFile1, out & 0x01, bit);
#endif
        break;
//     case 1:            // GPJ4_4//songwei
//     case 2:            // GPJ4_3//songwei
//     case 3:            // GPJ4_2//songwei
     case 1:            // GPJ4_1
     case 2:            // GPJ4_2
     case 3:            // GPJ4_3
//         bit = 5 - bit; //songwei
#ifndef WIN32
         ::ioctl(_ioFile2, out & 0x01, bit);
#endif
        break;
    }
}

bool RFIDChannelMan::data(int bit)
{
    unsigned long val = 0;
    switch(bit)
    {
    case 0:            // GPJ2_7
        read(_ioFile1, &val, sizeof(val));
        val &= (1 << 7);
        break;
    case 1:            // GPJ4_4
    case 2:            // GPJ4_3
    case 3:            // GPJ4_2
        bit = 5 - bit;
        read(_ioFile2, &val, sizeof(val));
        val &= (1 << bit);
        break;
    }
    return (val != 0);
}

void RFIDChannelMan::setData(int bit, bool highLevel)
{
    if((_ioFile1 < 0) || (_ioFile2 < 0))
       return;
    switch(bit)
    {
//    case 0:            // GPJ2_7 //songwei
    case 0:            // GPJ4_0
#ifndef WIN32
        ::ioctl(_ioFile1, 0x10 | highLevel, bit);
#endif
        break;
//    case 1:            // GPJ4_4//songwei
//    case 2:            // GPJ4_3//songwei
//    case 3:            // GPJ4_2//songwei
//        bit = 5 - bit;//songwei
    case 1:            // GPJ4_1
    case 2:            // GPJ4_2
    case 3:            // GPJ4_3
#ifndef WIN32
        ::ioctl(_ioFile2, 0x10 | highLevel, bit);
#endif
        break;
    }
}
#if 0
void RFIDChannelMan::setBeepDir(int bit, bool out)
{
#ifndef _WIN32
    ::ioctl(_beepFile, out, bit);
#endif
}


bool RFIDChannelMan::beepData(int bit)
{
    unsigned long val = 0;
    read(_beepFile, &val, sizeof(val));
    val &= (1 << bit);
    return (val != 0);
}


void RFIDChannelMan::setBeepData(int bit, bool highLevel)
{
#ifndef _WIN32
    ::ioctl(_beepFile, highLevel ? 0x11 : 0x10, bit);
#endif
}
#endif
void RFIDChannelMan::initPort()
{
    openPort();
    setDir(0, true);
    setDir(1, true);
    setDir(2, true);
//    setBeepDir(0, true);
//    setBeepDir(1, true);
//    setBeepDir(2, true);
    setChannel(ChannelInvalid);
//    selectBeep(ChannelInvalid);
}

#ifndef _WIN32
#include <QFile>
QString RFIDChannelMan::getRfidPort()
{
	bool  devFlag = 0;
	bool  devFlag1 = 0;

	devFlag = QFile("/sys/bus/usb-serial/devices/ttyUSB2").symLinkTarget().contains("1-1.1.4");

	if(devFlag)
		return QString(DEFAULT_RFID_COMM_DEV);
	else
	{
		devFlag1 = QFile("/sys/bus/usb-serial/devices/ttyUSB1").symLinkTarget().contains("1-1.1.4");

		if(devFlag1)
			return QString(CHANGE_RFID_COMM_DEV_1);
		else
			return QString(CHANGE_RFID_COMM_DEV_0);
    }
}
#endif

static RFIDChannelMan _dummy_instance_;
