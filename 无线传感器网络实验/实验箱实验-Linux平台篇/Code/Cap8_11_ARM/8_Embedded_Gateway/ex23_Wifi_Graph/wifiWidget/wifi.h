#ifndef WIFI_H
#define WIFI_H

#include <QWidget>
class QTimer;

namespace Ui {
    class Wifi;
}

class Wifi : public QWidget
{
    Q_OBJECT
    static float _lastTempValue;
    static float _lastHumiValue;
    static Wifi *_instance;

public:
    explicit Wifi(QWidget *parent = 0);
    ~Wifi();

    static float getLastTempValue() {
        return _lastTempValue;
    }
    static float getLastHumiValue() {
        return _lastHumiValue;
    }
    static void showOut() {
        if(_instance == NULL)
            _instance = new Wifi();
        _instance->show();
    }

private:
    Ui::Wifi *ui;
    QString wifiSrvIp;
    void *wifiCommUser;
    QTimer *wifiConnTimer;
    QTimer *updateTimer;

protected:
    virtual void showEvent(QShowEvent *e);
    virtual void hideEvent(QHideEvent *e);

protected slots:
    void reconnect();
    void reconnect(const QString &ip);
    void disconnect();
    void onUpdate();

    void updateNewData(const QString &ip, int endPoint, int funcCode, int funcID, const QByteArray &data);

signals:
    void newData(const QString &ip, int endPoint, int funcCode, int funcID, const QByteArray &data);
    void serverGone();

private:
    static void onNewData(void *arg, const char *nodeIP, int endPoint, int funcCode, int funcID, char *data, int len);
    static void onServerGone(void *arg);
};

#endif // WIFI_H
