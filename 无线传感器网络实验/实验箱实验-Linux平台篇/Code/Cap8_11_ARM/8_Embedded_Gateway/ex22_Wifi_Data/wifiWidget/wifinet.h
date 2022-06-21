#ifndef WIFINET_H
#define WIFINET_H

#include <QWidget>
#include <QDebug>
#include <libwificomm.h>

namespace Ui {
    class WifiNet;
}

class QTreeWidgetItem;
class QTimer;
class WifiNet : public QWidget
{
    Q_OBJECT

public:
    explicit WifiNet(QWidget *parent = 0);
    ~WifiNet();

protected:
    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *);

private:
    Ui::WifiNet *ui;
	QString wifiSrvIp;
	void *wifiCommUser;
	QTimer *wifiConnTimer;

	static float _lastTempValue;
	static float _lastHumiValue;
    static WifiNet *_instance;
public:
	static float getLastTempValue() {
		return _lastTempValue;
	}
	static float getLastHumiValue() {
		return _lastHumiValue;
	}
    static void showOut() {
        if(_instance == NULL)
            _instance = new WifiNet();
        _instance->show();
    }

signals:
	void newNode(const QString &ip, int funcNum, WIFI_NODE_FUNC *funcList);
	void newData(const QString &ip, int endPoint, int funcCode, int funcID, const QByteArray &data);
	void nodeGone(const QString &ip);
	void serverGone();

private slots:
	void updateNewNode(const QString &ip, int funcNum, WIFI_NODE_FUNC *funcList);
	void updateNewData(const QString &ip, int endPoint, int funcCode, int funcID, const QByteArray &data);
	void deleteNode(const QString &ip);

	void reconnect();
	void reconnect(const QString &ip);
	void disconnect();
//    void updataNodeInfo(QString ip, QString addr, QString value);

private:
	QTreeWidgetItem *createItem(const QString &ip, int endPoint, int funcCode, int funcID);
	QTreeWidgetItem *findItem(const QString &ip, int endPoint);
	static void onNewNode(void *arg, const char *nodeIP, int funcNum, WIFI_NODE_FUNC *funcList);
	static void onNewData(void *arg, const char *nodeIP, int endPoint, int funcCode, int funcID, char *data, int len);
	static void onNodeGone(void *arg, const char *nodeIP);
	static void onServerGone(void *arg);
};

#endif // WIFINET_H
