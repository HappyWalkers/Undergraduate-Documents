/****************************************************************************
** Meta object code from reading C++ file 'MjpgWidget.h'
**
** Created: Thu Aug 23 15:49:47 2018
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "MjpgWidget/MjpgWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MjpgWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MjpgWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      26,   12,   11,   11, 0x0a,
      75,   61,   11,   11, 0x0a,
     116,  106,   11,   11, 0x2a,
     144,  139,   11,   11, 0x2a,
     159,   11,   11,   11, 0x0a,
     166,   11,   11,   11, 0x0a,
     182,  174,   11,   11, 0x08,
     204,  199,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MjpgWidget[] = {
    "MjpgWidget\0\0user,password\0"
    "setAuthentication(QString,QString)\0"
    "host,port,uri\0start(QString,quint16,QString)\0"
    "host,port\0start(QString,quint16)\0host\0"
    "start(QString)\0stop()\0clear()\0errCode\0"
    "onHttpError(int)\0data\0onHttpResponse(QByteArray)\0"
};

const QMetaObject MjpgWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MjpgWidget,
      qt_meta_data_MjpgWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MjpgWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MjpgWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MjpgWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MjpgWidget))
        return static_cast<void*>(const_cast< MjpgWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int MjpgWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setAuthentication((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 1: start((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< quint16(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 2: start((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< quint16(*)>(_a[2]))); break;
        case 3: start((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: stop(); break;
        case 5: clear(); break;
        case 6: onHttpError((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: onHttpResponse((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
