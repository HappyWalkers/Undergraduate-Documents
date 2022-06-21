#ifndef SECURE_H
#define SECURE_H

#include <QWidget>
#include <libipv6comm.h>
#include <node_config.h>
#include <QTimer>
#ifdef _WIN32
#include <winsock2.h>
#endif

namespace Ui {
    class Ipv6Secure;
}

class Ipv6Secure : public QWidget
{
    Q_OBJECT

public:
    explicit Ipv6Secure(const QString &ip, quint8 id = 0xFF, QWidget *parent = 0);
    ~Ipv6Secure();

public slots:
    void reconnect(const QString &ip, quint8 id = 0xFF);

protected:
    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *);
    static void cbNewFunc(void *arg, unsigned char *nwkAddr, int funcNum, IPV6COMM_NODE_FUNC *funcList);
    static void cbNewData(void *arg, unsigned char *nwkAddr, int endPoint, int funcCode, int funcID, char *data, int len);
    static void cbNodeGone(void *arg, unsigned char *nwkAddr);

private:
    Ui::Ipv6Secure *ui;
    QString wsnSrvIp;
    quint8 funcID;
    QTimer *PicTimer;
    void *wsnSrvUser;
#if     1       //for IPV6
    QByteArray curNwkAddr;
#else
    unsigned short curNwkAddr;
#endif

protected:
    QPixmap pic[2];

signals:
    void nodeInfoChanged(QByteArray nwkAddr);
    void dataChanged(char data);

protected slots:
    void PicTimeout();
    void updateNodeInfo(QByteArray nwkAddr);
    void updateNodeData(char data);

public:
    static void showOut(const QString &ip, quint8 id = 0xFF);
};


#endif // SECURE_H
