/****************************************************************************
** Meta object code from reading C++ file 'dictwebview.h'
**
** Created: Sun Sep 9 13:30:09 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../dictwebview.h"
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dictwebview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DictWebView[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       6,   79, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   44,   58,   58, 0x05,
      59,   84,   58,   58, 0x05,
      90,   58,   58,   58, 0x05,
     111,   58,   58,   58, 0x05,
     125,   58,   58,   58, 0x05,
     140,  155,   58,   58, 0x05,
     160,  155,   58,   58, 0x05,

 // slots: signature, parameters, type, tag, flags
     177,   58,   58,   58, 0x0a,
     194,   58,   58,   58, 0x0a,
     208,   58,   58,   58, 0x0a,
     238,   58,   58,   58, 0x0a,
     269,   58,   58,   58, 0x0a,

 // methods: signature, parameters, type, tag, flags
     286,  300,   58,   58, 0x02,

 // properties: name, type, flags
     300,  304, 0x11095103,
     309,  323, 0x02095103,
     327,  323, 0x02095103,
     340,  356, (QMetaType::QReal << 24) | 0x00095103,
     362,  356, (QMetaType::QReal << 24) | 0x00095103,
     377,  356, (QMetaType::QReal << 24) | 0x00095103,

       0        // eod
};

static const char qt_meta_stringdata_DictWebView[] = {
    "DictWebView\0downloadProgress(qint64,qint64)\0"
    "current,total\0\0importCompleted(QString)\0"
    "dicts\0contentSizeChanged()\0linkClicked()\0"
    "loadFinished()\0movePage(bool)\0back\0"
    "hideButton(bool)\0followLink(QUrl)\0"
    "extractFile()\0handleContent(QNetworkReply*)\0"
    "handleContent(QNetworkRequest)\0"
    "handleMove(bool)\0load(QString)\0url\0"
    "QUrl\0contentHeight\0int\0contentWidth\0"
    "preferredHeight\0qreal\0preferredWidth\0"
    "zoomFactor\0"
};

const QMetaObject DictWebView::staticMetaObject = {
    { &QGraphicsProxyWidget::staticMetaObject, qt_meta_stringdata_DictWebView,
      qt_meta_data_DictWebView, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DictWebView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DictWebView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DictWebView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DictWebView))
        return static_cast<void*>(const_cast< DictWebView*>(this));
    return QGraphicsProxyWidget::qt_metacast(_clname);
}

int DictWebView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsProxyWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: downloadProgress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 1: importCompleted((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: contentSizeChanged(); break;
        case 3: linkClicked(); break;
        case 4: loadFinished(); break;
        case 5: movePage((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: hideButton((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: followLink((*reinterpret_cast< const QUrl(*)>(_a[1]))); break;
        case 8: extractFile(); break;
        case 9: handleContent((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 10: handleContent((*reinterpret_cast< const QNetworkRequest(*)>(_a[1]))); break;
        case 11: handleMove((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: load((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 13;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QUrl*>(_v) = url(); break;
        case 1: *reinterpret_cast< int*>(_v) = contentHeight(); break;
        case 2: *reinterpret_cast< int*>(_v) = contentWidth(); break;
        case 3: *reinterpret_cast< qreal*>(_v) = preferredHeight(); break;
        case 4: *reinterpret_cast< qreal*>(_v) = preferredWidth(); break;
        case 5: *reinterpret_cast< qreal*>(_v) = zoomFactor(); break;
        }
        _id -= 6;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setUrl(*reinterpret_cast< QUrl*>(_v)); break;
        case 1: setContentHeight(*reinterpret_cast< int*>(_v)); break;
        case 2: setContentWidth(*reinterpret_cast< int*>(_v)); break;
        case 3: setPreferredHeight(*reinterpret_cast< qreal*>(_v)); break;
        case 4: setPreferredWidth(*reinterpret_cast< qreal*>(_v)); break;
        case 5: setZoomFactor(*reinterpret_cast< qreal*>(_v)); break;
        }
        _id -= 6;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 6;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void DictWebView::downloadProgress(qint64 _t1, qint64 _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DictWebView::importCompleted(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void DictWebView::contentSizeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void DictWebView::linkClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void DictWebView::loadFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void DictWebView::movePage(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void DictWebView::hideButton(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_END_MOC_NAMESPACE
