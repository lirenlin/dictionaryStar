/****************************************************************************
** Meta object code from reading C++ file 'dictcore.h'
**
** Created: Sun Sep 9 13:30:08 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../dictcore.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dictcore.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DictCore[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      23,   14, // methods
       1,  129, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
       9,   24,   24,   24, 0x05,

 // methods: signature, parameters, type, tag, flags
      25,   49,   54,   24, 0x02,
      59,   49,   78,   24, 0x02,
      86,   49,  112,   24, 0x02,
     124,   49,  112,   24, 0x02,
     150,   24,   24,   24, 0x02,
     164,  203,   24,   24, 0x02,
     222,  240,   24,   24, 0x02,
     259,   24,   54,   24, 0x02,
     283,  311,   24,   24, 0x02,
     316,  350,   24,   24, 0x02,
     370,   24,   54,   24, 0x02,
     387,   24,   24,   24, 0x02,
     411,   24,  429,   24, 0x02,
     433,  457,   24,   24, 0x02,
     462,   24,   24,   24, 0x22,
     483,   24,  429,   24, 0x02,
     498,  457,   24,   24, 0x02,
     519,   24,   24,   24, 0x22,
     537,   24,   54,   24, 0x02,
     549,   24,   54,   24, 0x02,
     564,   24,   78,   24, 0x02,
     579,   24,   78,   24, 0x02,

 // properties: name, type, flags
     590,  596, 0x00495009,

 // properties: notify_signal_id
       0,

       0        // eod
};

static const char qt_meta_stringdata_DictCore[] = {
    "DictCore\0tableChanged()\0\0"
    "isTranslatable(QString)\0word\0bool\0"
    "translate(QString)\0QString\0"
    "findSimilarWords(QString)\0QStringList\0"
    "listSimilarWords(QString)\0updateModel()\0"
    "enableDictionary(QString,QString,bool)\0"
    "dict,plugin,enable\0moveItem(int,int)\0"
    "prevIndex,newIndex\0noEnabledDictionaries()\0"
    "enableDictionaries(QString)\0list\0"
    "deleteDictionary(QString,QString)\0"
    "pluginName,dictName\0predictiveText()\0"
    "setPredictiveText(bool)\0defaultFontSize()\0"
    "int\0setDefaultFontSize(int)\0size\0"
    "setDefaultFontSize()\0listFontSize()\0"
    "setListFontSize(int)\0setListFontSize()\0"
    "canGoBack()\0canGoForward()\0previousWord()\0"
    "nextWord()\0table\0TableModel*\0"
};

const QMetaObject DictCore::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_DictCore,
      qt_meta_data_DictCore, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DictCore::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DictCore::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DictCore::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DictCore))
        return static_cast<void*>(const_cast< DictCore*>(this));
    return QObject::qt_metacast(_clname);
}

int DictCore::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: tableChanged(); break;
        case 1: { bool _r = isTranslatable((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 2: { QString _r = translate((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 3: { QStringList _r = findSimilarWords((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = _r; }  break;
        case 4: { QStringList _r = listSimilarWords((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = _r; }  break;
        case 5: updateModel(); break;
        case 6: enableDictionary((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 7: moveItem((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 8: { bool _r = noEnabledDictionaries();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 9: enableDictionaries((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 10: deleteDictionary((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 11: { bool _r = predictiveText();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 12: setPredictiveText((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 13: { int _r = defaultFontSize();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 14: setDefaultFontSize((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: setDefaultFontSize(); break;
        case 16: { int _r = listFontSize();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 17: setListFontSize((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: setListFontSize(); break;
        case 19: { bool _r = canGoBack();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 20: { bool _r = canGoForward();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 21: { QString _r = previousWord();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 22: { QString _r = nextWord();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        default: ;
        }
        _id -= 23;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< TableModel**>(_v) = table(); break;
        }
        _id -= 1;
    } else if (_c == QMetaObject::WriteProperty) {
        _id -= 1;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void DictCore::tableChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
static const uint qt_meta_data_DictionariesModel[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_DictionariesModel[] = {
    "DictionariesModel\0"
};

const QMetaObject DictionariesModel::staticMetaObject = {
    { &QAbstractListModel::staticMetaObject, qt_meta_stringdata_DictionariesModel,
      qt_meta_data_DictionariesModel, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DictionariesModel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DictionariesModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DictionariesModel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DictionariesModel))
        return static_cast<void*>(const_cast< DictionariesModel*>(this));
    return QAbstractListModel::qt_metacast(_clname);
}

int DictionariesModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractListModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
