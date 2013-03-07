/****************************************************************************
** Meta object code from reading C++ file 'sqlmodel.h'
**
** Created: Sun Sep 9 13:30:10 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../sqlmodel.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sqlmodel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_sqlQueryModel[] = {

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

 // methods: signature, parameters, type, tag, flags
      14,   26,   32,   32, 0x02,
      33,   32,   32,   32, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_sqlQueryModel[] = {
    "sqlQueryModel\0remove(int)\0index\0\0"
    "loadDB()\0"
};

const QMetaObject sqlQueryModel::staticMetaObject = {
    { &QSqlQueryModel::staticMetaObject, qt_meta_stringdata_sqlQueryModel,
      qt_meta_data_sqlQueryModel, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &sqlQueryModel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *sqlQueryModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *sqlQueryModel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_sqlQueryModel))
        return static_cast<void*>(const_cast< sqlQueryModel*>(this));
    return QSqlQueryModel::qt_metacast(_clname);
}

int sqlQueryModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSqlQueryModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: remove((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: loadDB(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
