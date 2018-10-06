/****************************************************************************
** Meta object code from reading C++ file 'graphiccycle.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/graphiccycle.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'graphiccycle.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_graphicCycle_t {
    QByteArrayData data[20];
    char stringdata0[228];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_graphicCycle_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_graphicCycle_t qt_meta_stringdata_graphicCycle = {
    {
QT_MOC_LITERAL(0, 0, 12), // "graphicCycle"
QT_MOC_LITERAL(1, 13, 15), // "findCycleInTree"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 9), // "GiNaC::ex"
QT_MOC_LITERAL(4, 40, 5), // "cycle"
QT_MOC_LITERAL(5, 46, 12), // "sceneInvalid"
QT_MOC_LITERAL(6, 59, 19), // "changesMadeToFigure"
QT_MOC_LITERAL(7, 79, 15), // "MoebInv::figure"
QT_MOC_LITERAL(8, 95, 14), // "originalFigure"
QT_MOC_LITERAL(9, 110, 13), // "changedFigure"
QT_MOC_LITERAL(10, 124, 8), // "setHover"
QT_MOC_LITERAL(11, 133, 10), // "unsetHover"
QT_MOC_LITERAL(12, 144, 9), // "setColour"
QT_MOC_LITERAL(13, 154, 6), // "colour"
QT_MOC_LITERAL(14, 161, 12), // "setLineWidth"
QT_MOC_LITERAL(15, 174, 6), // "weight"
QT_MOC_LITERAL(16, 181, 12), // "setLineStyle"
QT_MOC_LITERAL(17, 194, 5), // "style"
QT_MOC_LITERAL(18, 200, 12), // "mouseStopped"
QT_MOC_LITERAL(19, 213, 14) // "cancelMovement"

    },
    "graphicCycle\0findCycleInTree\0\0GiNaC::ex\0"
    "cycle\0sceneInvalid\0changesMadeToFigure\0"
    "MoebInv::figure\0originalFigure\0"
    "changedFigure\0setHover\0unsetHover\0"
    "setColour\0colour\0setLineWidth\0weight\0"
    "setLineStyle\0style\0mouseStopped\0"
    "cancelMovement"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_graphicCycle[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x06 /* Public */,
       5,    0,   67,    2, 0x06 /* Public */,
       6,    2,   68,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    0,   73,    2, 0x0a /* Public */,
      11,    0,   74,    2, 0x0a /* Public */,
      12,    1,   75,    2, 0x0a /* Public */,
      14,    1,   78,    2, 0x0a /* Public */,
      16,    1,   81,    2, 0x0a /* Public */,
      18,    0,   84,    2, 0x0a /* Public */,
      19,    0,   85,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7, 0x80000000 | 7,    8,    9,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QColor,   13,
    QMetaType::Void, QMetaType::Double,   15,
    QMetaType::Void, QMetaType::Int,   17,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void graphicCycle::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        graphicCycle *_t = static_cast<graphicCycle *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->findCycleInTree((*reinterpret_cast< GiNaC::ex(*)>(_a[1]))); break;
        case 1: _t->sceneInvalid(); break;
        case 2: _t->changesMadeToFigure((*reinterpret_cast< const MoebInv::figure(*)>(_a[1])),(*reinterpret_cast< const MoebInv::figure(*)>(_a[2]))); break;
        case 3: _t->setHover(); break;
        case 4: _t->unsetHover(); break;
        case 5: _t->setColour((*reinterpret_cast< QColor(*)>(_a[1]))); break;
        case 6: _t->setLineWidth((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 7: _t->setLineStyle((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->mouseStopped(); break;
        case 9: _t->cancelMovement(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (graphicCycle::*)(GiNaC::ex );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&graphicCycle::findCycleInTree)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (graphicCycle::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&graphicCycle::sceneInvalid)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (graphicCycle::*)(const MoebInv::figure & , const MoebInv::figure & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&graphicCycle::changesMadeToFigure)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject graphicCycle::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_graphicCycle.data,
      qt_meta_data_graphicCycle,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *graphicCycle::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *graphicCycle::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_graphicCycle.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QGraphicsItem"))
        return static_cast< QGraphicsItem*>(this);
    return QObject::qt_metacast(_clname);
}

int graphicCycle::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void graphicCycle::findCycleInTree(GiNaC::ex _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void graphicCycle::sceneInvalid()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void graphicCycle::changesMadeToFigure(const MoebInv::figure & _t1, const MoebInv::figure & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
