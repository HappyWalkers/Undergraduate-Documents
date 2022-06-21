#ifndef MJPGWIDGET2_H
#define MJPGWIDGET2_H

#include <QWidget>
#include <QPixmap>
#include <MjpgWidget/HttpClientService.h>


//class HttpClientService;
class MjpgWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MjpgWidget(QWidget *parent = 0);
    ~MjpgWidget();

    bool isRunning() const;

public slots:
    void setAuthentication(const QString &user, const QString &password);
    void start(const QString &host, quint16 port = 80,
               const QString &uri = "/?action=stream");
    void stop();
    void clear();

protected:
    void paintEvent(QPaintEvent *ev);

private:
    HttpClientService *httpClient;
    QString _host;
    quint16 _port;
    QString uri;
    enum { ResponseHead, FrameHeader, FrameBody } socketStatus;
    QString boundary;
    QByteArray picData[2];
    int drawIdx, recvIdx;

    QString _user, _pwd;

private slots:
    void onHttpError(int errCode);
    void onHttpResponse(const QByteArray &data);
};

#endif // MJPGWIDGET2_H
