#ifndef RFIDCHANNELMAN_H
#define RFIDCHANNELMAN_H
#include <QObject>

class QTimer;

#ifndef _WIN32
#define DEFAULT_RFID_COMM_DEV   "/dev/ttyUSB2"
#define CHANGE_RFID_COMM_DEV_1  "/dev/ttyUSB1"
#define CHANGE_RFID_COMM_DEV_0  "/dev/ttyUSB0"
#endif

class RFIDChannelMan : public QObject
{
    Q_OBJECT
    static int _ioFile1;
    static int _ioFile2;
//    static int _beepFile;
    static RFIDChannelMan *_instance;
    QTimer *_timer;
public:
    enum {
        Channel125K = 0,
        ChannelIEEE14443,
        ChannelUHF900M,
        ChannelMicrowave,
        ChannelScanGun,
        ChannelInvalid
    };
    explicit RFIDChannelMan(QObject *parent = 0);
    ~RFIDChannelMan();

    static int channel();
    static void setChannel(int channel);
    static void selectBeep(int channel, int ms = 100);
#ifndef _WIN32
	static QString getRfidPort();
#endif

protected:
    static void openPort();
    static void closePort();
    static void setDir(int bit, bool out);
    static bool data(int bit);
    static void setData(int bit, bool highLevel);
//    static void setBeepDir(int bit, bool out);
//    static bool beepData(int bit);
//    static void setBeepData(int bit, bool highLevel);
    static void initPort();

private slots:
    void onTimeout();
};

#endif // RFIDCHANNELMAN_H
