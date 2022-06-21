/****************************************************************************
** Meta object code from reading C++ file 'HttpClientService.h'
**
** Created: Thu Aug 23 15:49:49 2018
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "MjpgWidget/HttpClientService.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'HttpClientService.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_HttpClientService[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      27,   19,   18,   18, 0x05,
      43,   38,   18,   18, 0x05,

 // slots: signature, parameters, type, tag, flags
      78,   64,   18,   18, 0x0a,
     117,  113,   18,   18, 0x0a,
     143,  130,   18,   18, 0x0a,
     165,  113,   18,   18, 0x2a,
     201,  179,   18,   18, 0x0a,
     281,  261,   18,   18, 0x08,
     344,  338,   18,   18, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_HttpClientService[] = {
    "HttpClientService\0\0errCode\0error(int)\0"
    "data\0response(QByteArray)\0user,password\0"
    "setAuthentication(QString,QString)\0"
    "url\0get(QString)\0url,formData\0"
    "post(QString,QString)\0post(QString)\0"
    "url,formData,fileList\0"
    "upload(QString,QMap<QString,QString>,QMap<QString,QString>)\0"
    "reply,authenticator\0"
    "onAuthenticationRequired(QNetworkReply*,QAuthenticator*)\0"
    "reply\0replyFinished(QNetworkReply*)\0"
};

const QMetaObject HttpClientService::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_HttpClientService,
      qt_meta_data_HttpClientService, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &HttpClientService::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *HttpClientService::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *HttpClientService::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_HttpClientService))
        return static_cast<void*>(const_cast< HttpClientService*>(this));
    return QObject::qt_metacast(_clname);
}

int HttpClientService::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: error((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: response((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 2: setAuthentication((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 3: get((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: post((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 5: post((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: upload((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QMap<QString,QString>(*)>(_a[2])),(*reinterpret_cast< const QMap<QString,QString>(*)>(_a[3]))); break;
        case 7: onAuthenticationRequired((*reinterpret_cast< QNetworkReply*(*)>(_a[1])),(*reinterpret_cast< QAuthenticator*(*)>(_a[2]))); break;
        case 8: replyFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void HttpClientService::error(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void HttpClientService::response(const QByteArray & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
static const uint qt_meta_data_HttpSyncConnHelper[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      28,   20,   19,   19, 0x0a,
      50,   45,   19,   19, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_HttpSyncConnHelper[] = {
    "HttpSyncConnHelper\0\0errCode\0"
    "onHttpError(int)\0data\0onHttpResponse(QByteArray)\0"
};

const QMetaObject HttpSyncConnHelper::staticMetaObject = {
    { &QEventLoop::staticMetaObject, qt_meta_stringdata_HttpSyncConnHelper,
      qt_meta_data_HttpSyncConnHelper, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &HttpSyncConnHelper::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *HttpSyncConnHelper::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *HttpSyncConnHelper::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_HttpSyncConnHelper))
        return static_cast<void*>(const_cast< HttpSyncConnHelper*>(this));
    return QEventLoop::qt_metacast(_clname);
}

int HttpSyncConnHelper::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QEventLoop::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: onHttpError((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: onHttpResponse((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
