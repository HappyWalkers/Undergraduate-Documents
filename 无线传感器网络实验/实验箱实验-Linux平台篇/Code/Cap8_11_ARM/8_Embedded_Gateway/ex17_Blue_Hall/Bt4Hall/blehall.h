#ifndef BLEHALL_H
#define BLEHALL_H

#include <QWidget>
#include <libbt4comm.h>
#include <node_config.h>
#include <QTimer>

#ifdef _WIN32
#include <winsock2.h>
#endif

namespace Ui {
    class BleHall;
}

class BleHall : public QWidget
{
    Q_OBJECT

public:
    explicit BleHall(const QString &ip, quint8 id = 0xFF, QWidget *parent = 0);
    ~BleHall();

public slots:
    void reconnect(const QString &ip, quint8 id = 0xFF);

private:
    Ui::BleHall *ui;
    QPixmap pic[2];
    QString wsnSrvIp;
    QTimer *timer;
    quint8 funcID;
    void *wsnSrvUser;
    //unsigned short curNwkAddr;
    QByteArray curNwkAddr;
    bool hallAlarmFlag;

protected:
    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *);
    static void cbNewFunc(void *arg, unsigned char *nwkAddr, int funcNum, BT4COMM_NODE_FUNC *funcList);
    static void cbNewData(void *arg, unsigned char *nwkAddr, int endPoint, int funcCode, int funcID, char *data, int len);
    static void cbNodeGone(void *arg, unsigned char *nwkAddr);

signals:
    void nodeInfoChanged(QByteArray nwkAddr);
    void gotNewNodeData(char v);
    void gotBleHallAlarm(const char *hallAlarm);

protected slots:
    void updateNodeInfo(QByteArray nwkAddr);
    void updateNodeData(char v);
    void timeOut(void);

public:
     static void showOut(const QString &ip, quint8 id = 0xFF);
};

#endif // BLEHALL_H
