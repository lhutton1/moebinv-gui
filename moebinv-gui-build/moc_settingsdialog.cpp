/****************************************************************************
** Meta object code from reading C++ file 'settingsdialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/settingsdialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'settingsdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_settingsDialog_t {
    QByteArrayData data[22];
    char stringdata0[424];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_settingsDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_settingsDialog_t qt_meta_stringdata_settingsDialog = {
    {
QT_MOC_LITERAL(0, 0, 14), // "settingsDialog"
QT_MOC_LITERAL(1, 15, 12), // "sceneInvalid"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 19), // "setBackgroundColour"
QT_MOC_LITERAL(4, 49, 6), // "colour"
QT_MOC_LITERAL(5, 56, 23), // "saveDirectoryHasChanged"
QT_MOC_LITERAL(6, 80, 6), // "update"
QT_MOC_LITERAL(7, 87, 26), // "on_automaticNaming_clicked"
QT_MOC_LITERAL(8, 114, 7), // "checked"
QT_MOC_LITERAL(9, 122, 23), // "on_manualNaming_clicked"
QT_MOC_LITERAL(10, 146, 21), // "on_pushButton_pressed"
QT_MOC_LITERAL(11, 168, 23), // "on_pushButton_2_pressed"
QT_MOC_LITERAL(12, 192, 23), // "on_pushButton_3_pressed"
QT_MOC_LITERAL(13, 216, 24), // "on_onlyRealsTrue_clicked"
QT_MOC_LITERAL(14, 241, 25), // "on_onlyRealsFalse_clicked"
QT_MOC_LITERAL(15, 267, 33), // "on_defaultPathLineEdit_textEd..."
QT_MOC_LITERAL(16, 301, 4), // "arg1"
QT_MOC_LITERAL(17, 306, 23), // "on_pushButton_4_clicked"
QT_MOC_LITERAL(18, 330, 23), // "on_spinBox_valueChanged"
QT_MOC_LITERAL(19, 354, 31), // "on_doubleSpinBox_2_valueChanged"
QT_MOC_LITERAL(20, 386, 31), // "on_comboBox_currentIndexChanged"
QT_MOC_LITERAL(21, 418, 5) // "index"

    },
    "settingsDialog\0sceneInvalid\0\0"
    "setBackgroundColour\0colour\0"
    "saveDirectoryHasChanged\0update\0"
    "on_automaticNaming_clicked\0checked\0"
    "on_manualNaming_clicked\0on_pushButton_pressed\0"
    "on_pushButton_2_pressed\0on_pushButton_3_pressed\0"
    "on_onlyRealsTrue_clicked\0"
    "on_onlyRealsFalse_clicked\0"
    "on_defaultPathLineEdit_textEdited\0"
    "arg1\0on_pushButton_4_clicked\0"
    "on_spinBox_valueChanged\0"
    "on_doubleSpinBox_2_valueChanged\0"
    "on_comboBox_currentIndexChanged\0index"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_settingsDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x06 /* Public */,
       3,    1,   95,    2, 0x06 /* Public */,
       5,    0,   98,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   99,    2, 0x08 /* Private */,
       7,    1,  100,    2, 0x08 /* Private */,
       9,    1,  103,    2, 0x08 /* Private */,
      10,    0,  106,    2, 0x08 /* Private */,
      11,    0,  107,    2, 0x08 /* Private */,
      12,    0,  108,    2, 0x08 /* Private */,
      13,    1,  109,    2, 0x08 /* Private */,
      14,    1,  112,    2, 0x08 /* Private */,
      15,    1,  115,    2, 0x08 /* Private */,
      17,    0,  118,    2, 0x08 /* Private */,
      18,    1,  119,    2, 0x08 /* Private */,
      19,    1,  122,    2, 0x08 /* Private */,
      20,    1,  125,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QColor,    4,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    8,
    QMetaType::Void, QMetaType::Bool,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    8,
    QMetaType::Void, QMetaType::Bool,    8,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void, QMetaType::Double,   16,
    QMetaType::Void, QMetaType::Int,   21,

       0        // eod
};

void settingsDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        settingsDialog *_t = static_cast<settingsDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sceneInvalid(); break;
        case 1: _t->setBackgroundColour((*reinterpret_cast< QColor(*)>(_a[1]))); break;
        case 2: _t->saveDirectoryHasChanged(); break;
        case 3: _t->update(); break;
        case 4: _t->on_automaticNaming_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->on_manualNaming_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->on_pushButton_pressed(); break;
        case 7: _t->on_pushButton_2_pressed(); break;
        case 8: _t->on_pushButton_3_pressed(); break;
        case 9: _t->on_onlyRealsTrue_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->on_onlyRealsFalse_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: _t->on_defaultPathLineEdit_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 12: _t->on_pushButton_4_clicked(); break;
        case 13: _t->on_spinBox_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->on_doubleSpinBox_2_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 15: _t->on_comboBox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (settingsDialog::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&settingsDialog::sceneInvalid)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (settingsDialog::*)(QColor );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&settingsDialog::setBackgroundColour)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (settingsDialog::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&settingsDialog::saveDirectoryHasChanged)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject settingsDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_settingsDialog.data,
      qt_meta_data_settingsDialog,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *settingsDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *settingsDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_settingsDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int settingsDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void settingsDialog::sceneInvalid()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void settingsDialog::setBackgroundColour(QColor _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void settingsDialog::saveDirectoryHasChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
