#ifndef IEEE14443CONTROLWIDGET_H
#define IEEE14443CONTROLWIDGET_H

#include <QObject>

class QextSerialPort;
class QTimer;
class IEEE14443Control : public QObject
{
    Q_OBJECT

public:
    enum IEEE14443Cmd { Idle, GetCardId, ReadCard, WriteCard, AntiControl, WalletInit, WalletGet, WalletCharge, WalletRecharge };
    explicit IEEE14443Control(QObject *parent = 0);
    ~IEEE14443Control();

    bool isActive() const;
    IEEE14443Cmd currentCmd() const { return lastOperation; }

public slots:
    bool start(const QString &port);
    void stop();
    void closeAnti();
    void openAnti();
    bool getCardId();
    bool readCard(int block);
    bool writeCard(int block, const QByteArray &data);
    bool walletInit(int block, int money);
    bool walletGet(int block);
    bool walletCharge(int block, int money);
    bool walletRecharge(int block, int money);

signals:
    // public signals
    void error(int cmdType, const QString &result);
    void foundCard(const QByteArray &cardid);
    void dataReaded(int block, const QByteArray &data);
    void dataWritten(int block);

    void walletInitialised(int block);
    void walletGetted(int block, int money);
    void walletCharged(int block);
    void walletRecharged(int block);

signals:
    // internal signals
    void recvPackage(QByteArray pkg);

private:
    QextSerialPort *commPort;
    QByteArray lastSendPackage;
    int recvStatus;
    QByteArray lastRecvPackage;
	QTimer *commTimer;

    IEEE14443Cmd lastOperation;
    int lastBlock;
    int walletMoney;
    QByteArray lastCardId;
    QByteArray lastCardData;

private:
    bool sendData(const QByteArray &data);

private slots:
    void process_walletRecharge();
    void process_walletCharge();
    void process_walletGet();
    void process_walletInit();
    void process_write();
    void process_read();
    void process_authCheck();
    void process_selCard();
    void process_getId();
	void process_searchCard();
	void process_antiControl(int on);
	void onCommTimeOut();

    //void on_clearDisplayBtn_clicked();
    void onPortDataReady();
    void onRecvedPackage(QByteArray pkg);
};

#endif // IEEE14443CONTROLWIDGET_H
