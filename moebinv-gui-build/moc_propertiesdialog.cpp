/****************************************************************************
** Meta object code from reading C++ file 'propertiesdialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/propertiesdialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'propertiesdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_propertiesDialog_t {
    QByteArrayData data[12];
    char stringdata0[301];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_propertiesDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_propertiesDialog_t qt_meta_stringdata_propertiesDialog = {
    {
QT_MOC_LITERAL(0, 0, 16), // "propertiesDialog"
QT_MOC_LITERAL(1, 17, 36), // "on_figureDescriptionText_text..."
QT_MOC_LITERAL(2, 54, 0), // ""
QT_MOC_LITERAL(3, 55, 22), // "on_floatButton_clicked"
QT_MOC_LITERAL(4, 78, 7), // "checked"
QT_MOC_LITERAL(5, 86, 22), // "on_exactButton_clicked"
QT_MOC_LITERAL(6, 109, 30), // "on_ellipticPointButton_clicked"
QT_MOC_LITERAL(7, 140, 31), // "on_parabolicPointButton_clicked"
QT_MOC_LITERAL(8, 172, 32), // "on_hyperbolicPointButton_clicked"
QT_MOC_LITERAL(9, 205, 30), // "on_ellipticCycleButton_clicked"
QT_MOC_LITERAL(10, 236, 31), // "on_parabolicCycleButton_clicked"
QT_MOC_LITERAL(11, 268, 32) // "on_hyperbolicCycleButton_clicked"

    },
    "propertiesDialog\0on_figureDescriptionText_textChanged\0"
    "\0on_floatButton_clicked\0checked\0"
    "on_exactButton_clicked\0"
    "on_ellipticPointButton_clicked\0"
    "on_parabolicPointButton_clicked\0"
    "on_hyperbolicPointButton_clicked\0"
    "on_ellipticCycleButton_clicked\0"
    "on_parabolicCycleButton_clicked\0"
    "on_hyperbolicCycleButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_propertiesDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x08 /* Private */,
       3,    1,   60,    2, 0x08 /* Private */,
       5,    1,   63,    2, 0x08 /* Private */,
       6,    1,   66,    2, 0x08 /* Private */,
       7,    1,   69,    2, 0x08 /* Private */,
       8,    1,   72,    2, 0x08 /* Private */,
       9,    1,   75,    2, 0x08 /* Private */,
      10,    1,   78,    2, 0x08 /* Private */,
      11,    1,   81,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, QMetaType::Bool,    4,

       0        // eod
};

void propertiesDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        propertiesDialog *_t = static_cast<propertiesDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_figureDescriptionText_textChanged(); break;
        case 1: _t->on_floatButton_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->on_exactButton_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->on_ellipticPointButton_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->on_parabolicPointButton_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->on_hyperbolicPointButton_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->on_ellipticCycleButton_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->on_parabolicCycleButton_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->on_hyperbolicCycleButton_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject propertiesDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_propertiesDialog.data,
      qt_meta_data_propertiesDialog,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *propertiesDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *propertiesDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_propertiesDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int propertiesDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
