#ifndef BLELIGHT_H
#define BLELIGHT_H

#include <QWidget>
#include <libbt4comm.h>
#include <node_config.h>
#include <QTimer>

#ifdef _WIN32
#include <winsock2.h>
#endif

namespace Ui {
    class BleIllum;
}

class BleIllum : public QWidget
{
    Q_OBJECT

public:
    explicit BleIllum(const QString &ip, quint8 id = 0xFF, QWidget *parent = 0);
    ~BleIllum();

public slots:
    void reconnect(const QString &ip, quint8 id = 0xFF);

private:
    Ui::BleIllum *ui;

    QString wsnSrvIp;
    quint8 funcID;
    void *wsnSrvUser;
    //unsigned short curNwkAddr;
    QByteArray curNwkAddr;

protected:
    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *);
    static void cbNewFunc(void *arg, unsigned char *nwkAddr, int funcNum, BT4COMM_NODE_FUNC *funcList);
    static void cbNewData(void *arg, unsigned char *nwkAddr, int endPoint, int funcCode, int funcID, char *data, int len);
    static void cbNodeGone(void *arg, unsigned char *nwkAddr);

signals:
    void nodeInfoChanged(QByteArray nwkAddr);
    void gotNewNodeData(unsigned short v);

protected slots:
    void updateNodeInfo(QByteArray nwkAddr);
    void updateNodeData(unsigned short v);

public:
     static void showOut(const QString &ip, quint8 id = 0xFF);
};

#endif // BLELIGHT_H
