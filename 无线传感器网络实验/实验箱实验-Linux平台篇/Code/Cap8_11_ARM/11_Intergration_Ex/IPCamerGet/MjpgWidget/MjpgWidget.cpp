#include "MjpgWidget.h"
#include "HttpClientService.h"
#include <QPainter>
#include <QHttp>
#include <QUrl>
#include <QDebug>

MjpgWidget::MjpgWidget(QWidget *parent) :
    QWidget(parent),
    httpClient(NULL),
    _host("127.0.0.1"), _port(80),
    uri("/?action=stream"),
    drawIdx(0), recvIdx(1)
{
}

MjpgWidget::~MjpgWidget()
{
    if(httpClient)
    {
        httpClient->deleteLater();
    }
}

bool MjpgWidget::isRunning() const
{
    return (httpClient != NULL);
}

void MjpgWidget::paintEvent(QPaintEvent *ev)
{
    Q_UNUSED(ev);
    QPainter pt(this);
    QRect rc;
    QPixmap pixmap;
    pixmap.loadFromData(picData[drawIdx]);
    rc = this->geometry();
    pt.drawPixmap(0, 0, rc.width(), rc.height(), pixmap);
}

void MjpgWidget::setAuthentication(const QString &user, const QString &password)
{
    _user = user;
    _pwd = password;
    if(httpClient != NULL)
        httpClient->setAuthentication(_user, _pwd);
}

void MjpgWidget::start(const QString &host, quint16 port, const QString &uri)
{
    if(httpClient != NULL)
        return;

    this->uri = uri;
    socketStatus = ResponseHead;
    qDebug()<<"==22==Mjpg start uri:"<<uri;
    httpClient = new HttpClientService(this);

    connect(httpClient, SIGNAL(error(int)), this, SLOT(onHttpError(int)));
    connect(httpClient, SIGNAL(response(QByteArray)),
            this, SLOT(onHttpResponse(QByteArray)));

    _host = host;
    _port = port;
    qDebug()<<"==66==Mjpg start host&port:"<<host<<port;
    httpClient->setAuthentication(_user, _pwd);
    httpClient->get(QString("http://%1:%2%3").arg(_host).arg(_port).arg(uri));
}

void MjpgWidget::stop()
{
    if(httpClient == NULL)
        return;
    httpClient->disconnect();
    httpClient->deleteLater();
    httpClient = NULL;
}

void MjpgWidget::clear()
{
    picData[drawIdx].clear();
    update();
}

void MjpgWidget::onHttpError(int errCode)
{
    qDebug()<<"Http Mjpg Error code:"<<errCode;
    stop();
    httpClient->get("http://"+_host+":"+_port+uri);

}

void MjpgWidget::onHttpResponse(const QByteArray &data)
{
    picData[recvIdx] = data;
    drawIdx = recvIdx;
    recvIdx = !recvIdx;
    update();
    httpClient->get(QString("http://%1:%2%3").arg(_host).arg(_port).arg(uri));
}
