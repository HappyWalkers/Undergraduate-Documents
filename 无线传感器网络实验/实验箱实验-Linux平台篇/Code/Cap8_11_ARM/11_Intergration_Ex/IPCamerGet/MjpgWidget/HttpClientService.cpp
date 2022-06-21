/**
  @file HttpClientService.cpp
  @brief HTTP客户端常用请求方法的实现
  */
#include "HttpClientService.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QAuthenticator>
#include <QTimer>
#include <qjson/parser.h>
#include <QDebug>

HttpClientService::HttpClientService(QObject *parent) :
    QObject(parent), _autoDelete(false)
{
    _manager = new QNetworkAccessManager(this);
    qDebug()<<"==44==HttpClientService start: "<<_autoDelete;
    connect(_manager, SIGNAL(authenticationRequired(QNetworkReply*,QAuthenticator*)),
            this, SLOT(onAuthenticationRequired(QNetworkReply*,QAuthenticator*)));
    connect(_manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));
}

HttpClientService::HttpClientService(const QObject *receiver,
                                     const char *response,
                                     const char *error, QObject *parent) :
    QObject(parent), _autoDelete(true)
{
    _manager = new QNetworkAccessManager(this);

    qDebug()<<"==3333==HttpClientService start :"<<_autoDelete;
    connect(_manager, SIGNAL(authenticationRequired(QNetworkReply*,QAuthenticator*)),
            this, SLOT(onAuthenticationRequired(QNetworkReply*,QAuthenticator*)));
    connect(_manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));

    connect(this, SIGNAL(error(int)), receiver, error);
    connect(this, SIGNAL(response(QByteArray)), receiver, response);
}

HttpClientService::~HttpClientService()
{
    delete _manager;
}

void HttpClientService::replyFinished(QNetworkReply *reply)
{
    if(reply && reply->error() == QNetworkReply::NoError)
    {
        emit response(reply->readAll());
    }
    else
    {
        emit error((int)reply->error());
    }
    reply->close();
    reply->deleteLater();
    if(_autoDelete)
        deleteLater();
}

void HttpClientService::onAuthenticationRequired(QNetworkReply *reply, QAuthenticator *authenticator)
{
    Q_UNUSED(reply);

    qDebug()<<"==55==authen :"<<_user<<_pwd;
    authenticator->setUser(_user);
    authenticator->setPassword(_pwd);
}

void HttpClientService::setAuthentication(const QString &user, const QString &password)
{

    qDebug()<<"user and password:"<<user<<password;
    _user = user;
    _pwd = password;
}

void HttpClientService::get(const QString &url)
{
    QNetworkRequest request;
    request.setUrl(QUrl(url));

    qDebug()<<"==77==Mjpg get request:"<<url;
    _manager->get(request);
}

// formData must be already convert to PercentEncoding
void HttpClientService::post(const QString &url, const QString &formData)
{
    QNetworkRequest request;
    request.setUrl(QUrl(url));
    if(!formData.isEmpty())
    {
        QByteArray data = formData.toUtf8();
        data.replace(" ", "+");//QUrl::toPercentEncoding(formData, "?=+&");
        request.setHeader(QNetworkRequest::ContentTypeHeader,
                          "application/x-www-form-urlencoded");
        request.setHeader(QNetworkRequest::ContentLengthHeader,
                          data.length());
        _manager->post(request, data);
    }
    else
        _manager->post(request, QByteArray());
}

#include <QDateTime>
#include <QFile>
#include <QFileInfo>
void HttpClientService::upload(const QString &url,
                               const QMap<QString, QString> &formData,
                               const QMap<QString, QString> &fileList)
{
    QNetworkRequest request;
    request.setUrl(QUrl(url));
    if(!formData.isEmpty() || !fileList.isEmpty())
    {
        QString boundary = QString("%1%2%3")
                .arg(QDateTime::currentDateTime().toTime_t())
                .arg(qrand()).arg(qrand());
        request.setHeader(QNetworkRequest::ContentTypeHeader,
                          "multipart/form-data; boundary="+boundary);
        QByteArray multiPartData;
        QMapIterator<QString, QString> formDataWalker(formData);
        while(formDataWalker.hasNext())
        {
            formDataWalker.next();
            QString formPart =
                    QString(
                        "--%1\r\n"
                        "Content-Disposition: form-data; name=\"%2\"\r\n"
                        "Content-Type: text/plain; charset=UTF-8\r\n\r\n"
                        "%3\r\n"
                        ).arg(boundary).arg(formDataWalker.key())
                    .arg(formDataWalker.value());
            multiPartData.append(formPart.toUtf8());
        }
        QMapIterator<QString, QString> fileWalker(fileList);
        while(fileWalker.hasNext())
        {
            fileWalker.next();
            QFileInfo fi(fileWalker.value());
            if(!fi.exists())
                continue;
            QString filePart =
                    QString(
                        "--%1\r\n"
                        "Content-Disposition: form-data; name=\"%2\"; filename=\"%3\"\r\n"
                        "Content-Type: application/octet-stream\r\n\r\n"
                        ).arg(boundary).arg(fileWalker.key()).arg(fi.fileName());
            multiPartData.append(filePart.toUtf8());
            QFile f(fi.absoluteFilePath());
            f.open(QIODevice::ReadOnly);
            QByteArray fileContent = f.readAll();
            multiPartData.append(fileContent);
            multiPartData.append("\r\n");
        }
        multiPartData.append(QString("--%1--\r\n").arg(boundary).toUtf8());
        _manager->post(request, multiPartData);
    }
    else
        _manager->post(request, QByteArray());
}

void HttpClientService::get(const QString &url,
                            const QObject *receiver,
                            const char *response, const char *error)
{
    HttpClientService *httpClient =
            new HttpClientService(receiver,
                                  response, error, NULL);
    httpClient->get(url);
}

void HttpClientService::post(const QString &url, const QString &formData,
                             const QObject *receiver,
                             const char *response, const char *error)
{
    HttpClientService *httpClient =
            new HttpClientService(receiver,
                                  response, error, NULL);
    httpClient->post(url, formData);
}

void HttpClientService::upload(const QString &url,
                               const QMap<QString, QString> &formData,
                               const QMap<QString, QString> &fileList,
                               const QObject *receiver,
                               const char *response, const char *error)
{
    HttpClientService *httpClieht =
            new HttpClientService(receiver, response, error, NULL);
    httpClieht->upload(url, formData, fileList);
}

bool HttpClientService::get(const QString &url, QByteArray &response, int timeout)
{
    HttpSyncConnHelper helper;
    HttpClientService::get(url, &helper,
                           SLOT(onHttpResponse(QByteArray)),
                           SLOT(onHttpError(int)));
    helper.exec();
    if(helper.error() == 0)
        response = helper.getResponse();
    return (helper.error() == 0);
}

QVariant HttpClientService::getJson(const QString &url, int timeout)
{
    QByteArray r;
    if(!get(url, r, timeout))
    {
//        qDebug()<<"getJson"<<url<<"failed";
        return QVariant();
    }
    qDebug()<<"getJson"<<url<<"result:"<<r;
    return QJson::Parser().parse(QUrl::fromPercentEncoding(r).toUtf8());
}

bool HttpClientService::post(const QString &url, const QString &formData,
                             QByteArray &response, int timeout)
{
    HttpSyncConnHelper helper;
    HttpClientService::post(url, formData, &helper,
                            SLOT(onHttpResponse(QByteArray)),
                            SLOT(onHttpError(int)));
    helper.exec();
    if(helper.error() == 0)
        response = helper.getResponse();
    return (helper.error() == 0);
}

QVariant HttpClientService::postJson(const QString &url, const QString &formData, int timeout)
{
    QByteArray r;
    if(!post(url, formData, r, timeout))
    {
//        qDebug()<<"postJson"<<url<<"failed";
        return QVariant();
    }
    qDebug()<<"postJson"<<url<<formData<<"result:"<<r;
    return QJson::Parser().parse(QUrl::fromPercentEncoding(r).toUtf8());
}

bool HttpClientService::upload(const QString &url,
                               const QMap<QString, QString> &formData,
                               const QMap<QString, QString> &fileList,
                               QByteArray &response, int timeout)
{
    HttpSyncConnHelper helper;
    HttpClientService::upload(url, formData, fileList, &helper,
                              SLOT(onHttpResponse(QByteArray)),
                              SLOT(onHttpError(int)));
    helper.exec();
    if(helper.error() == 0)
        response = helper.getResponse();
    return (helper.error() == 0);
}

HttpSyncConnHelper::HttpSyncConnHelper(QObject *parent)
    : QEventLoop(parent), _error(0)
{
}

int HttpSyncConnHelper::error() const
{
    return _error;
}

const QByteArray HttpSyncConnHelper::getResponse() const
{
    return _response;
}

void HttpSyncConnHelper::onHttpError(int errCode)
{
    _error = errCode;
    quit();
}

void HttpSyncConnHelper::onHttpResponse(const QByteArray &data)
{
    _error = 0;
    _response = data;
    quit();
}
