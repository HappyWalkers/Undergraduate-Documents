#ifndef ID125KCONTROL_H
#define ID125KCONTROL_H

#include <QObject>
#include <QByteArray>

class QextSerialPort;
class QTimer;
class ID125KControl : public QObject
{
    Q_OBJECT
    const static int _IDLength;
public:
    explicit ID125KControl(QObject *parent = 0);
    ~ID125KControl();

    bool isActive() const;

    static unsigned long toDecID(const QByteArray &byteID) { return toDecID(byteID.constData()); }
    static unsigned long toDecID(const char *id);

signals:
    void newCard(unsigned long decID, const QByteArray &byteID);

public slots:
    bool start(const QString &port);
    void stop();

private slots:
    void onCommPortDataReady();
    void onTimeout();

private:
    QextSerialPort *_commPort;
    QTimer *_timer;
    QByteArray _lastRecvedBytes;
};

#endif // ID125KCONTROL_H
