#ifndef RLM100LOWLEVELOPERATION_H
#define RLM100LOWLEVELOPERATION_H

#include <QObject>

class QextSerialPort;
class QTimer;
class RLM100Package;
class QEventLoop;
class RLM100Control : public QObject
{
    Q_OBJECT
private:
	QextSerialPort *commPort;
	QByteArray lastRecvedPackage;
    QEventLoop *_syncHelper;

	QTimer *timer;
    QTimer *syncTimer;

    quint8 _respStatus;
    QByteArray _respData;

public:
    enum Sections {
        SectionReserved = 0x00,
        SectionEPC, SectionTID, SectionUser
    };

    explicit RLM100Control(QObject *parent = 0);
    ~RLM100Control();

	bool isActive() const;
    bool isBusy() const;

public slots:
	void start(const QString &port);
	void stop();

signals:
    void timeout();
    void newEPC(const QByteArray &uii);

private slots:
    void onPortDataReady();
    void onPackageReadyHook(const RLM100Package &pkg);
    void onOpTimeout();

    void writeCommand(const RLM100Package &pkg);

public slots:
    // 基础操作
    bool getStatus();
    int getPower();
    bool setPower(int power);
    bool getFrequency() {return false;}
    bool setFrequency() {return false;}
#if 0       // not support on RLM100
    bool readReg(quint16 startAddr, quint16 len, QByteArray &regs);
    bool writeReg(quint16 startAddr, const QByteArray &regs);
    bool resetReg();
    bool saveReg();
#endif
    bool getVersion(QByteArray &hwSerial, QByteArray &swVersion);
    //bool getUID(QByteArray &uid);
    bool sleep();
    bool stopOperation();
    // 标签盘点
    bool singleScan(QByteArray &uii);
    bool startSingleScanLoop();
    bool startMultiScanLoop(int q = 3);
    // 标签数据操作
    bool readCard(QByteArray &outData, const QByteArray &uii, Sections section, uint startAddress, int len = 0, const QByteArray &apwd = QByteArray(4, 0));
    bool read(QByteArray &outData, QByteArray &outUII, Sections section, uint startAddress, int len = 0, const QByteArray &apwd = QByteArray(4, 0));
    bool writeCard1Word(const QByteArray &data, const QByteArray &uii, Sections section, uint startAddress, const QByteArray &apwd = QByteArray(4, 0));
    bool write1Word(const QByteArray &data, QByteArray &outUII, Sections section, uint startAddress, const QByteArray &apwd = QByteArray(4, 0));
    bool writeCard(const QByteArray &data, const QByteArray &uii, Sections section, uint startAddress, const QByteArray &apwd = QByteArray(4, 0));
    bool write(const QByteArray &data, QByteArray &outUII, Sections section, uint startAddress, const QByteArray &apwd = QByteArray(4, 0));
    bool eraseCard(const QByteArray &uii, Sections section, uint startAddress, int len, const QByteArray &apwd = QByteArray(4, 0));
    bool erase(QByteArray &outUII, Sections section, uint startAddress, int len, const QByteArray &apwd = QByteArray(4, 0));
};

#endif // RLM100LOWLEVELOPERATION_H
