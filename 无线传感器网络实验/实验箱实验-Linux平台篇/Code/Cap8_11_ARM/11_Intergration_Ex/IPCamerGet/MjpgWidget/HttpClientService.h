/**
  @file HttpClientService.h
  @brief HTTP客户端常用请求方法的封装
  */
#ifndef HTTPCLIENTSERVICE_H
#define HTTPCLIENTSERVICE_H

#include <QObject>
#include <QVariant>

class QNetworkAccessManager;
class QNetworkReply;
class QAuthenticator;
/**
 * @brief HTTP客户端常用请求方法的封装
 *
 * HttpClientService主要封装了GET和POST两类请求方法。<br />
 * 同时，针对这两类请求方法，分别提供了：
 * - 信号/槽
 * - 异步（通过槽函数获得异步通知）
 * - 同步（通过EventLoop等待请求完成）
 * 三种不同的调用方式。<br />
 * 另外，在该类中还提供了针对通过POST方式上传文件的操作的封装，极大的方便了基于C++完成B/S架构程序的开发。<br />
 */
class HttpClientService : public QObject
{
    Q_OBJECT
    explicit HttpClientService(const QObject *receiver,
                               const char *response, const char *error,
                               QObject *parent = 0);
public:
    /**
     * @brief 构造函数，用于信号/槽的调用方式下，自行创建HttpClientService对象，并处理各种信号
     * @param[in] parent 父对象指针
     */
    explicit HttpClientService(QObject *parent = 0);
    ~HttpClientService();

    // 异步操作函数
    /**
     * @brief 异步方式的GET请求
     * @param[in] url 请求的URL地址
     * @param[in] receiver 请求结束后异步槽函数的所属对象
     * @param[in] response 请求结束后，如果请求成功，需要执行的槽函数<br />
     * 该槽函数必须与本类的信号 @ref response 的形式保持一致
     * @param[in] error 请求结束后，如果请求失败，需要执行的槽函数<br />
     * 该槽函数必须与本类的信号 @ref error 的形式保持一致
     *
     * @par 示例
     * @code
     * class TestHandler public QObject {
     *     Q_OBJECT
     * public:
     *     TestHandler(QObject *parent = 0);
     *
     * public slots:
     *     void onResponse(const QByteArray &data)
     *     {
     *         // data中保存了此次请求得到的从服务器返回的数据
     *         // do something with data
     *     }
     *     void onError(int errCode)
     *     {
     *         // 请求失败,errCode保存了错误类型
     *     }
     * };
     *
     * TestHandler handler;
     * HttpClientService::get("http://127.0.0.1/?text1=xxx&text2=yyy",
     *     &handler, SLOT(onResponse(QByteArray)), SLOT(onError(int)));
     * @endcode
     */
    static void get(const QString &url,
                    const QObject *receiver,
                    const char *response, const char *error);
    /**
     * @brief 异步方式的POST请求
     *
     * 该函数模拟了"x-www-form-urlencoded"类型的表单的请求过程
     * @param[in] url 请求的URL地址
     * @param[in] formData 通过POST请求发送的表单数据
     * @param[in] receiver 请求结束后异步槽函数的所属对象
     * @param[in] response 请求结束后，如果请求成功，需要执行的槽函数<br />
     * 该槽函数必须与本类的信号 @ref response 的形式保持一致
     * @param[in] error 请求结束后，如果请求失败，需要执行的槽函数<br />
     * 该槽函数必须与本类的信号 @ref error 的形式保持一致
     *
     * @note 表单数据 \a formData 应当是"name1=value1&name2=value2"形式的百分号编码的字符串
     *
     * @par 示例
     * @code
     * class TestHandler public QObject {
     *     Q_OBJECT
     * public:
     *     TestHandler(QObject *parent = 0);
     *
     * public slots:
     *     void onResponse(const QByteArray &data)
     *     {
     *         // data中保存了此次请求得到的从服务器返回的数据
     *         // do something with data
     *     }
     *     void onError(int errCode)
     *     {
     *         // 请求失败,errCode保存了错误类型
     *     }
     * };
     *
     * TestHandler handler;
     * HttpClientService::post("http://127.0.0.1/", "text1=xxx&text2=yyy",
     *     &handler, SLOT(onResponse(QByteArray)), SLOT(onError(int)));
     * @endcode
     */
    static void post(const QString &url, const QString &formData,
                     const QObject *receiver,
                     const char *response, const char *error);
    // formData中的key即为表单name,value即为表单value
    // fileList中的key即为表单name,value即为待上传的本地文件路径
    /**
     * @brief 异步方式通过POST方式上传文件
     *
     * 该函数模拟了"multipart/form-data"类型的表单的请求过程
     * @param[in] url 请求的URL地址
     * @param[in] formData 表单列表
     * @param[in] fileList 需要上传的文件列表
     * @param[in] receiver 请求结束后异步槽函数的所属对象
     * @param[in] response 请求结束后，如果请求成功，需要执行的槽函数<br />
     * 该槽函数必须与本类的信号 @ref response 的形式保持一致
     * @param[in] error 请求结束后，如果请求失败，需要执行的槽函数<br />
     * 该槽函数必须与本类的信号 @ref error 的形式保持一致
     *
     * @note \a formData 是一个表，这个表的每一个key代表了一个表单的name，而它的value则是这个表单的value。<br />
     * \a fileList 也是一个标，这个表的每一个key代表了一个file类型的表单的name，而它的value则是这个文件的本地路径。
     *
     * @par 示例
     * @code
     * class TestHandler public QObject {
     *     Q_OBJECT
     * public:
     *     TestHandler(QObject *parent = 0);
     *
     * public slots:
     *     void onResponse(const QByteArray &data)
     *     {
     *         // data中保存了此次请求得到的从服务器返回的数据
     *         // do something with data
     *     }
     *     void onError(int errCode)
     *     {
     *         // 请求失败,errCode保存了错误类型
     *     }
     * };
     *
     * TestHandler handler;
     * // 构建表单数据列表
     * QMap<QString, QString> formData;
     * formData["text1"] = "xxx";
     * formData["text2"] = "yyy";
     * // 构建上传的文件列表
     * QMap<QString, QString> fileList;
     * fileList["file1"] = "C:/test.jpg";
     * fileList["file2"] = "D:/test.pdf";
     * HttpClientService::upload("http://127.0.0.1/", formData, fileList,
     *     &handler, SLOT(onResponse(QByteArray)), SLOT(onError(int)));
     * @endcode
     */
    static void upload(const QString &url,
                       const QMap<QString, QString> &formData,
                       const QMap<QString, QString> &fileList,
                       const QObject *receiver,
                       const char *response, const char *error);

    // 同步操作函数
    /**
     * @brief 同步方式的GET请求
     * @param[in] url 请求的URL地址
     * @param[out] response 保存从服务器返回的响应数据
     * @param[in] timeout 超时时间（默认值为0）<br />
     * 当设置为0时表示使用系统的TCP通信超时时间
     * @return 请求是否成功
     * @retval true 请求成功
     * @retval false 请求失败
     *
     * @par 示例
     * @code
     * QByteArray resp;
     * HttpClientService::get("http://127.0.0.1/?text1=xxx&text2=yyy", resp);
     * // resp里保存的即为从服务器返回的数据
     * @endcode
     */
    static bool get(const QString &url,
                    QByteArray &response,
                    int timeout = 0);
    /**
     * @brief 同步方式的GET请求，同时将返回的数据解析为JSON对象
     * @param[in] url 请求的URL地址
     * @param[in] timeout 超时时间（默认值为0）<br />
     * 当设置为0时表示使用系统的TCP通信超时时间
     * @return 从服务器返回的JSON对象
     * @note 可以通过调用返回的QVariant对象的isNull()方法来判断请求是否成功
     *
     * @par 示例
     * @code
     * QVariant obj = HttpClientService::getJson("http://127.0.0.1/?text1=xxx&text2=yyy");
     * if(!obj.isNull())
     * {
     *     // 得到服务器返回的JSON数据
     *     // 可以将其转换为JSON对象：QVariantMap objMap = obj.toMap();
     *     // 或者将其转换为JSON数组：QVariantList objList = obj.toList();
     * }
     * @endcode
     */
    static QVariant getJson(const QString &url, int timeout = 0);
    /**
     * @brief 同步方式的POST请求
     * @param[in] url 请求的URL地址
     * @param[in] formData 通过POST请求发送的表单数据
     * @param[out] response 保存从服务器返回的响应数据
     * @param[in] timeout 超时时间（默认值为0）<br />
     * 当设置为0时表示使用系统的TCP通信超时时间
     * @return 请求是否成功
     * @retval true 请求成功
     * @retval false 请求失败
     *
     * @par 示例
     * @code
     * QByteArray resp;
     * HttpClientService::post("http://127.0.0.1/", "text1=xxx&text2=yyy", resp);
     * // resp里保存的即为从服务器返回的数据
     * @endcode
     */
    static bool post(const QString &url, const QString &formData,
                     QByteArray &response,
                     int timeout = 0);
    /**
     * @brief 同步方式的POST请求，同时将返回的数据解析为JSON对象
     * @param[in] url 请求的URL地址
     * @param[in] formData 通过POST请求发送的表单数据
     * @param[in] timeout 超时时间（默认值为0）<br />
     * 当设置为0时表示使用系统的TCP通信超时时间
     * @return 从服务器返回的JSON对象
     * @note 可以通过调用返回的QVariant对象的isNull()方法来判断请求是否成功
     *
     * @par 示例
     * @code
     * QVariant obj = HttpClientService::postJson("http://127.0.0.1/", "text1=xxx&text2=yyy");
     * if(!obj.isNull())
     * {
     *     // 得到服务器返回的JSON数据
     *     // 可以将其转换为JSON对象：QVariantMap objMap = obj.toMap();
     *     // 或者将其转换为JSON数组：QVariantList objList = obj.toList();
     * }
     * @endcode
     */
    static QVariant postJson(const QString &url, const QString &formData,
                         int timeout = 0);
    // formData中的key即为表单name,value即为表单value
    // fileList中的key即为表单name,value即为待上传的本地文件路径
    /**
     * @brief 同步方式通过POST方式上传文件
     * @param[in] url 请求的URL地址
     * @param[in] formData 表单列表
     * @param[in] fileList 需要上传的文件列表
     * @param response 保存从服务器返回的响应数据
     * @param timeout 超时时间（默认值为0）<br />
     * 当设置为0时表示使用系统的TCP通信超时时间
     * @return 请求是否成功
     * @retval true 请求成功
     * @retval false 请求失败
     * @note 该函数模拟了"multipart/form-data"类型的表单的请求过程
     *
     * @note \a formData 是一个表，这个表的每一个key代表了一个表单的name，而它的value则是这个表单的value。<br />
     * \a fileList 也是一个标，这个表的每一个key代表了一个file类型的表单的name，而它的value则是这个文件的本地路径。
     *
     * @par 示例
     * @code
     * QByteArray resp;
     * // 构建表单数据列表
     * QMap<QString, QString> formData;
     * formData["text1"] = "xxx";
     * formData["text2"] = "yyy";
     * // 构建上传的文件列表
     * QMap<QString, QString> fileList;
     * fileList["file1"] = "C:/test.jpg";
     * fileList["file2"] = "D:/test.pdf";
     * HttpClientService::upload("http://127.0.0.1/", formData, fileList, resp);
     * // resp里保存的即为从服务器返回的数据
     * @endcode
     */
    static bool upload(const QString &url,
                       const QMap<QString, QString> &formData,
                       const QMap<QString, QString> &fileList,
                       QByteArray &response, int timeout = 0);

signals:
    /**
     * @brief 请求出错
     *
     * 当请求（无论是GET还是POST）出错时会发出此信号
     * @param errCode 错误类型，具体可以参考QNetworkReply::NetworkError
     */
    void error(int errCode);
    /**
     * @brief 请求完成
     *
     * 当请求（无论是GET还是POST）正常完成后会发出此信号
     * @param data 保存了服务器返回的数据
     */
    void response(const QByteArray &data);

public slots:

    void setAuthentication(const QString &user, const QString &password);
    /**
     * @brief 向服务器发起GET请求
     * @param[in] url 请求的URL地址
     *
     * @par 示例
     * @code
     * class TestHandler public QObject {
     *     Q_OBJECT
     * public:
     *     TestHandler(QObject *parent = 0);
     *
     * public slots:
     *     void onResponse(const QByteArray &data)
     *     {
     *         // data中保存了此次请求得到的从服务器返回的数据
     *         // do something with data
     *     }
     *     void onError(int errCode)
     *     {
     *         // 请求失败,errCode保存了错误类型
     *     }
     * };
     *
     * TestHandler handler;
     * HttpClientServer httpClient;
     * connect(&httpClient, SIGNAL(response(QByteArray)),
     *          &handler, SLOT(onResponse(QByteArray)));
     * connect(&httpClient, SIGNAL(error(int)),
     *          &handler, SLOT(onError(int)));
     * httpClient.get("http://127.0.0.1/?text1=xxx&text2=yyy");
     * @endcode
     */
    void get(const QString &url);
    /**
     * @brief 向服务器发起POST请求
     *
     * 该函数模拟了"x-www-form-urlencoded"类型的表单的请求过程
     * @param[in] url 请求的URL地址
     * @param[in] formData 通过POST请求发送的表单数据
     *
     * @note 表单数据 \a formData 应当是"name1=value1&name2=value2"形式的百分号编码的字符串
     *
     * @par 示例
     * @code
     * class TestHandler public QObject {
     *     Q_OBJECT
     * public:
     *     TestHandler(QObject *parent = 0);
     *
     * public slots:
     *     void onResponse(const QByteArray &data)
     *     {
     *         // data中保存了此次请求得到的从服务器返回的数据
     *         // do something with data
     *     }
     *     void onError(int errCode)
     *     {
     *         // 请求失败,errCode保存了错误类型
     *     }
     * };
     *
     * TestHandler handler;
     * HttpClientServer httpClient;
     * connect(&httpClient, SIGNAL(response(QByteArray)),
     *          &handler, SLOT(onResponse(QByteArray)));
     * connect(&httpClient, SIGNAL(error(int)),
     *          &handler, SLOT(onError(int)));
     * httpClient.post("http://127.0.0.1/", "text1=xxx&text2=yyy");
     * @endcode
     */
    void post(const QString &url, const QString &formData = QString());
    // formData中的key即为表单name,value即为表单value
    // fileList中的key即为表单name,value即为待上传的本地文件路径
    /**
     * @brief 通过POST方式上传文件
     *
     * 该函数模拟了"multipart/form-data"类型的表单的请求过程
     * @param[in] url 请求的URL地址
     * @param[in] formData 表单列表
     * @param[in] fileList 需要上传的文件列表
     *
     * @note \a formData 是一个表，这个表的每一个key代表了一个表单的name，而它的value则是这个表单的value。<br />
     * \a fileList 也是一个标，这个表的每一个key代表了一个file类型的表单的name，而它的value则是这个文件的本地路径。
     *
     * @par 示例
     * @code
     * class TestHandler public QObject {
     *     Q_OBJECT
     * public:
     *     TestHandler(QObject *parent = 0);
     *
     * public slots:
     *     void onResponse(const QByteArray &data)
     *     {
     *         // data中保存了此次请求得到的从服务器返回的数据
     *         // do something with data
     *     }
     *     void onError(int errCode)
     *     {
     *         // 请求失败,errCode保存了错误类型
     *     }
     * };
     *
     * TestHandler handler;
     * HttpClientServer httpClient;
     * connect(&httpClient, SIGNAL(response(QByteArray)),
     *          &handler, SLOT(onResponse(QByteArray)));
     * connect(&httpClient, SIGNAL(error(int)),
     *          &handler, SLOT(onError(int)));
     * // 构建表单数据列表
     * QMap<QString, QString> formData;
     * formData["text1"] = "xxx";
     * formData["text2"] = "yyy";
     * // 构建上传的文件列表
     * QMap<QString, QString> fileList;
     * fileList["file1"] = "C:/test.jpg";
     * fileList["file2"] = "D:/test.pdf";
     * httpClient.upload("http://127.0.0.1/", formData, fileList);
     * @endcode
     */
    void upload(const QString &url, const QMap<QString, QString> &formData,
                const QMap<QString, QString> &fileList);

private slots:
    void onAuthenticationRequired(QNetworkReply *reply, QAuthenticator *authenticator);
    void replyFinished(QNetworkReply* reply);

private:
    bool _autoDelete;
    QNetworkAccessManager *_manager;

    QString _user;
    QString _pwd;
};

#include <QEventLoop>
/**
 * @brief 用于实现同步方式的GET/POST请求的辅助类，用户不需要直接调用
 */
class HttpSyncConnHelper : public QEventLoop
{
    Q_OBJECT
public:
    /**
     * @brief 构造函数
     * @param parent 父对象指针
     */
    HttpSyncConnHelper(QObject *parent = 0);

    /**
     * @brief 得到上一次操作的错误代码
     * @return 错误代码，具体参考QNetworkReply::NetworkError
     */
    int error() const;
    /**
     * @brief 得到从服务器返回的响应数据
     * @return
     */
    const QByteArray getResponse() const;

private:
    int _error;
    QByteArray _response;

public slots:
    /**
     * @brief 用来处理请求失败的槽函数
     * @param errCode 错误代码
     */
    void onHttpError(int errCode);
    /**
     * @brief 用来处理请求成功的槽函数
     * @param data 从服务器返回的响应数据
     */
    void onHttpResponse(const QByteArray &data);
};

#endif // HTTPCLIENTSERVICE_H
