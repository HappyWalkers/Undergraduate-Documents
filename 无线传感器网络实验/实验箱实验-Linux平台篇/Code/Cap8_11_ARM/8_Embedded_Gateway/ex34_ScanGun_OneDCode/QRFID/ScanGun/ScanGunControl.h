#ifndef SCANGUNCONTROL_H
#define SCANGUNCONTROL_H

#include <QObject>
#include <QByteArray>

class QextSerialPort;
class QTimer;
class ScanGunControl : public QObject
{
    Q_OBJECT
public:
    explicit ScanGunControl(QObject *parent = 0);
    ~ScanGunControl();

    bool isActive() const;

signals:
    void scanResult(const QByteArray &result);

public slots:
    bool start(const QString &port);
    void stop();

private slots:
    void onCommPortDataReady();
    void onTimeout();
    void reportScanResult();

private:
    QextSerialPort *_commPort;
    QTimer *_timer;
    QByteArray _lastRecvedBytes;
};

#endif // SCANGUNCONTROL_H
