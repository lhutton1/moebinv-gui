/****************************************************************************
** Meta object code from reading C++ file 'cyclecontextmenu.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/cyclecontextmenu.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cyclecontextmenu.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_cycleContextMenu_t {
    QByteArrayData data[21];
    char stringdata0[294];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_cycleContextMenu_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_cycleContextMenu_t qt_meta_stringdata_cycleContextMenu = {
    {
QT_MOC_LITERAL(0, 0, 16), // "cycleContextMenu"
QT_MOC_LITERAL(1, 17, 20), // "relationsHaveChanged"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 14), // "colourSelected"
QT_MOC_LITERAL(4, 54, 6), // "colour"
QT_MOC_LITERAL(5, 61, 14), // "weightSelected"
QT_MOC_LITERAL(6, 76, 6), // "weight"
QT_MOC_LITERAL(7, 83, 13), // "styleSelected"
QT_MOC_LITERAL(8, 97, 5), // "style"
QT_MOC_LITERAL(9, 103, 12), // "sceneInvalid"
QT_MOC_LITERAL(10, 116, 19), // "changesMadeToFigure"
QT_MOC_LITERAL(11, 136, 15), // "MoebInv::figure"
QT_MOC_LITERAL(12, 152, 14), // "originalFigure"
QT_MOC_LITERAL(13, 167, 13), // "changedFigure"
QT_MOC_LITERAL(14, 181, 18), // "confirmDeleteCycle"
QT_MOC_LITERAL(15, 200, 17), // "amendRelationList"
QT_MOC_LITERAL(16, 218, 6), // "metric"
QT_MOC_LITERAL(17, 225, 19), // "displayColourDialog"
QT_MOC_LITERAL(18, 245, 18), // "displayStyleDialog"
QT_MOC_LITERAL(19, 264, 19), // "displayWeightDialog"
QT_MOC_LITERAL(20, 284, 9) // "editPoint"

    },
    "cycleContextMenu\0relationsHaveChanged\0"
    "\0colourSelected\0colour\0weightSelected\0"
    "weight\0styleSelected\0style\0sceneInvalid\0"
    "changesMadeToFigure\0MoebInv::figure\0"
    "originalFigure\0changedFigure\0"
    "confirmDeleteCycle\0amendRelationList\0"
    "metric\0displayColourDialog\0"
    "displayStyleDialog\0displayWeightDialog\0"
    "editPoint"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_cycleContextMenu[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x06 /* Public */,
       3,    1,   75,    2, 0x06 /* Public */,
       5,    1,   78,    2, 0x06 /* Public */,
       7,    1,   81,    2, 0x06 /* Public */,
       9,    0,   84,    2, 0x06 /* Public */,
      10,    2,   85,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      14,    0,   90,    2, 0x0a /* Public */,
      15,    1,   91,    2, 0x0a /* Public */,
      17,    0,   94,    2, 0x0a /* Public */,
      18,    0,   95,    2, 0x0a /* Public */,
      19,    0,   96,    2, 0x0a /* Public */,
      20,    0,   97,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QColor,    4,
    QMetaType::Void, QMetaType::Double,    6,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 11, 0x80000000 | 11,   12,   13,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   16,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void cycleContextMenu::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        cycleContextMenu *_t = static_cast<cycleContextMenu *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->relationsHaveChanged(); break;
        case 1: _t->colourSelected((*reinterpret_cast< QColor(*)>(_a[1]))); break;
        case 2: _t->weightSelected((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: _t->styleSelected((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->sceneInvalid(); break;
        case 5: _t->changesMadeToFigure((*reinterpret_cast< const MoebInv::figure(*)>(_a[1])),(*reinterpret_cast< const MoebInv::figure(*)>(_a[2]))); break;
        case 6: _t->confirmDeleteCycle(); break;
        case 7: _t->amendRelationList((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 8: _t->displayColourDialog(); break;
        case 9: _t->displayStyleDialog(); break;
        case 10: _t->displayWeightDialog(); break;
        case 11: _t->editPoint(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (cycleContextMenu::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&cycleContextMenu::relationsHaveChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (cycleContextMenu::*)(QColor );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&cycleContextMenu::colourSelected)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (cycleContextMenu::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&cycleContextMenu::weightSelected)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (cycleContextMenu::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&cycleContextMenu::styleSelected)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (cycleContextMenu::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&cycleContextMenu::sceneInvalid)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (cycleContextMenu::*)(const MoebInv::figure & , const MoebInv::figure & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&cycleContextMenu::changesMadeToFigure)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject cycleContextMenu::staticMetaObject = {
    { &QMenu::staticMetaObject, qt_meta_stringdata_cycleContextMenu.data,
      qt_meta_data_cycleContextMenu,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *cycleContextMenu::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *cycleContextMenu::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_cycleContextMenu.stringdata0))
        return static_cast<void*>(this);
    return QMenu::qt_metacast(_clname);
}

int cycleContextMenu::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMenu::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void cycleContextMenu::relationsHaveChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void cycleContextMenu::colourSelected(QColor _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void cycleContextMenu::weightSelected(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void cycleContextMenu::styleSelected(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void cycleContextMenu::sceneInvalid()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void cycleContextMenu::changesMadeToFigure(const MoebInv::figure & _t1, const MoebInv::figure & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
