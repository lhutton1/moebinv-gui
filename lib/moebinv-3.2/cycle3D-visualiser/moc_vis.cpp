/****************************************************************************
** Meta object code from reading C++ file 'vis.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "vis.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'vis.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_vis_t {
    QByteArrayData data[23];
    char stringdata0[265];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_vis_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_vis_t qt_meta_stringdata_vis = {
    {
QT_MOC_LITERAL(0, 0, 3), // "vis"
QT_MOC_LITERAL(1, 4, 10), // "setColSlot"
QT_MOC_LITERAL(2, 15, 0), // ""
QT_MOC_LITERAL(3, 16, 5), // "colID"
QT_MOC_LITERAL(4, 22, 13), // "colChangeSlot"
QT_MOC_LITERAL(5, 36, 18), // "transSliderChanged"
QT_MOC_LITERAL(6, 55, 3), // "val"
QT_MOC_LITERAL(7, 59, 15), // "transChangeSlot"
QT_MOC_LITERAL(8, 75, 21), // "printIntersectionSlot"
QT_MOC_LITERAL(9, 97, 2), // "id"
QT_MOC_LITERAL(10, 100, 14), // "updateDrawList"
QT_MOC_LITERAL(11, 115, 21), // "printAllIntersections"
QT_MOC_LITERAL(12, 137, 20), // "drawAllIntersections"
QT_MOC_LITERAL(13, 158, 17), // "createSlideDialog"
QT_MOC_LITERAL(14, 176, 12), // "setSlideshow"
QT_MOC_LITERAL(15, 189, 9), // "keyChange"
QT_MOC_LITERAL(16, 199, 3), // "key"
QT_MOC_LITERAL(17, 203, 11), // "transChange"
QT_MOC_LITERAL(18, 215, 5), // "trans"
QT_MOC_LITERAL(19, 221, 11), // "groupChange"
QT_MOC_LITERAL(20, 233, 5), // "group"
QT_MOC_LITERAL(21, 239, 14), // "takeScreenshot"
QT_MOC_LITERAL(22, 254, 10) // "fileLoader"

    },
    "vis\0setColSlot\0\0colID\0colChangeSlot\0"
    "transSliderChanged\0val\0transChangeSlot\0"
    "printIntersectionSlot\0id\0updateDrawList\0"
    "printAllIntersections\0drawAllIntersections\0"
    "createSlideDialog\0setSlideshow\0keyChange\0"
    "key\0transChange\0trans\0groupChange\0"
    "group\0takeScreenshot\0fileLoader"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_vis[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   89,    2, 0x0a /* Public */,
       4,    0,   92,    2, 0x0a /* Public */,
       5,    1,   93,    2, 0x0a /* Public */,
       7,    0,   96,    2, 0x0a /* Public */,
       8,    1,   97,    2, 0x0a /* Public */,
      10,    0,  100,    2, 0x0a /* Public */,
      11,    0,  101,    2, 0x0a /* Public */,
      12,    0,  102,    2, 0x0a /* Public */,
      13,    0,  103,    2, 0x0a /* Public */,
      14,    0,  104,    2, 0x0a /* Public */,
      15,    1,  105,    2, 0x0a /* Public */,
      17,    1,  108,    2, 0x0a /* Public */,
      19,    1,  111,    2, 0x0a /* Public */,
      21,    0,  114,    2, 0x0a /* Public */,
      22,    0,  115,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   18,
    QMetaType::Void, QMetaType::QString,   20,
    QMetaType::Void,
    QMetaType::Int,

       0        // eod
};

void vis::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        vis *_t = static_cast<vis *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setColSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->colChangeSlot(); break;
        case 2: _t->transSliderChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->transChangeSlot(); break;
        case 4: _t->printIntersectionSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->updateDrawList(); break;
        case 6: _t->printAllIntersections(); break;
        case 7: _t->drawAllIntersections(); break;
        case 8: _t->createSlideDialog(); break;
        case 9: _t->setSlideshow(); break;
        case 10: _t->keyChange((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 11: _t->transChange((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 12: _t->groupChange((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 13: _t->takeScreenshot(); break;
        case 14: { int _r = _t->fileLoader();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject vis::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_vis.data,
      qt_meta_data_vis,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *vis::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *vis::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_vis.stringdata0))
        return static_cast<void*>(this);
    return QGLWidget::qt_metacast(_clname);
}

int vis::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
