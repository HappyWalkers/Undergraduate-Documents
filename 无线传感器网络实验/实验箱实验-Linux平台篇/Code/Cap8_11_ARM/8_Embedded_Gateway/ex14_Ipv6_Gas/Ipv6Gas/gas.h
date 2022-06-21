#ifndef GAS_H
#define GAS_H

#include <QWidget>
#include <libipv6comm.h>
#include <node_config.h>
#ifdef _WIN32
#include <winsock2.h>
#endif
#include <QTimer>


namespace Ui {
    class Ipv6Gas;
}

class Ipv6Gas : public QWidget
{
    Q_OBJECT

public:
    explicit Ipv6Gas(const QString &ip, quint8 id = 0xFF, QWidget *parent = 0);
    ~Ipv6Gas();

public slots:
    void reconnect(const QString &ip, quint8 id = 0xFF);

private:
    Ui::Ipv6Gas *ui;
    QPixmap pic[2];
    QString wsnSrvIp;
    QTimer *timer;
    quint8 funcID;
    void *wsnSrvUser;
#if     1       //for IPV6
    QByteArray curNwkAddr;
#else
    unsigned short curNwkAddr;
#endif
    bool gasAlarmFlag;

protected:
    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *);
    static void cbNewFunc(void *arg, unsigned char *nwkAddr, int funcNum, IPV6COMM_NODE_FUNC *funcList);
    static void cbNewData(void *arg, unsigned char *nwkAddr, int endPoint, int funcCode, int funcID, char *data, int len);
    static void cbNodeGone(void *arg, unsigned char *nwkAddr);

signals:
    void nodeInfoChanged(QByteArray nwkAddr);
    void gotNewNodeData(char v);
    void gotIpv6GasAlarm(const char *gasAlarm);

protected slots:
    void updateNodeInfo(QByteArray nwkAddr);
    void updateNodeData(char v);


public:
     static void showOut(const QString &ip, quint8 id = 0xFF);
};

#endif // GAS_H
