/****************************************************************************
** Meta object code from reading C++ file 'ID125KControl.h'
**
** Created: Sun Nov 25 02:02:26 2018
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../QRFID/ID125K/ID125KControl.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ID125KControl.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ID125KControl[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      28,   15,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      64,   59,   54,   14, 0x0a,
      79,   14,   14,   14, 0x0a,
      86,   14,   14,   14, 0x08,
     108,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ID125KControl[] = {
    "ID125KControl\0\0decID,byteID\0"
    "newCard(ulong,QByteArray)\0bool\0port\0"
    "start(QString)\0stop()\0onCommPortDataReady()\0"
    "onTimeout()\0"
};

const QMetaObject ID125KControl::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ID125KControl,
      qt_meta_data_ID125KControl, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ID125KControl::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ID125KControl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ID125KControl::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ID125KControl))
        return static_cast<void*>(const_cast< ID125KControl*>(this));
    return QObject::qt_metacast(_clname);
}

int ID125KControl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: newCard((*reinterpret_cast< ulong(*)>(_a[1])),(*reinterpret_cast< const QByteArray(*)>(_a[2]))); break;
        case 1: { bool _r = start((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 2: stop(); break;
        case 3: onCommPortDataReady(); break;
        case 4: onTimeout(); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void ID125KControl::newCard(unsigned long _t1, const QByteArray & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
