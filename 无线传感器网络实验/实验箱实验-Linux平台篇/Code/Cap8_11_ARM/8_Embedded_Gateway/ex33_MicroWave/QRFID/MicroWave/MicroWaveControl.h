#ifndef MICROWAVECONTROL_H
#define MICROWAVECONTROL_H
#include <QObject>

#define MICROWAVE_HEAD          0xFF
#define MICROWAVE_HEAD_SIZE     5
#define MICROWAVE_PKG_SIZE      12

class QextSerialPort;
class MicroWaveControl : public QObject
{
    Q_OBJECT
public:
    enum CardType {
        Normal = 1,         // 普通卡
        Temperature,        // 温度卡
        TempHumi,           // 温湿度卡
        PreventDemolition,  // 防拆卡
        Tamper = 0x0C       // 防拆异常卡
    };

    explicit MicroWaveControl(QObject *parent = 0);
    ~MicroWaveControl();

    bool isActive() const;

    static unsigned long toDecID(const QByteArray &byteID) { return toDecID(byteID.constData()); }
    static unsigned long toDecID(const char *id);

signals:
    void newCard(int readerAddr, int cardType, bool lowPower, unsigned long decID, const QByteArray &byteID);

public slots:
    bool start(const QString &port);
    void stop();

private slots:
    void onCommPortDataReady();

private:
    QextSerialPort *_commPort;
    QByteArray _lastRecvedBytes;
};

#endif // MICROWAVECONTROL_H
