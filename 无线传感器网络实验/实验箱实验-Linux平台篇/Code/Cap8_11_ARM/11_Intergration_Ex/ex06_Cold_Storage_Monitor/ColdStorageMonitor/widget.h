#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "ColdStorageSetting.h"
#include <libwificomm.h>

namespace Ui {
    class Widget;
}

class QTimer;
class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
    QString wifiSrvIp;
    void *wifiCommUser;
    QTimer *wifiConnTimer;

signals:
    void newNode(const QString &ip, int funcNum, WIFI_NODE_FUNC *funcList);
    void newData(const QString &ip, int endPoint, int funcCode, int funcID, const QByteArray &data);
    void nodeGone(const QString &ip);
    void serverGone();

    void newTempNodeValue(const QString &ip, int endPoint, int funcID, float value);

private slots:
    void updateNewNode(const QString &ip, int funcNum, WIFI_NODE_FUNC *funcList);
    void updateNewData(const QString &ip, int endPoint, int funcCode, int funcID, const QByteArray &data);
    void deleteNode(const QString &ip);

    void reconnect();
    void reconnect(const QString &ip);
    void disconnect();

    void on_openCloseBtn_clicked(bool checked);

private:
    static void onNewNode(void *arg, const char *nodeIP, int funcNum, WIFI_NODE_FUNC *funcList);
    static void onNewData(void *arg, const char *nodeIP, int endPoint, int funcCode, int funcID, char *data, int len);
    static void onNodeGone(void *arg, const char *nodeIP);
    static void onServerGone(void *arg);

};

#endif // WIDGET_H
