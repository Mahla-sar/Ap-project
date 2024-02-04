/****************************************************************************
** Meta object code from reading C++ file 'edit_pro.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../edit_pro.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'edit_pro.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSedit_proENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSedit_proENDCLASS = QtMocHelpers::stringData(
    "edit_pro",
    "pro_deleted",
    "",
    "name",
    "name_changed",
    "before",
    "after",
    "content_refreshed",
    "on_namebutton_clicked",
    "on_add_button_clicked",
    "on_deletbutton_clicked",
    "on_remove_clicked",
    "on_button_clicked"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSedit_proENDCLASS_t {
    uint offsetsAndSizes[26];
    char stringdata0[9];
    char stringdata1[12];
    char stringdata2[1];
    char stringdata3[5];
    char stringdata4[13];
    char stringdata5[7];
    char stringdata6[6];
    char stringdata7[18];
    char stringdata8[22];
    char stringdata9[22];
    char stringdata10[23];
    char stringdata11[18];
    char stringdata12[18];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSedit_proENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSedit_proENDCLASS_t qt_meta_stringdata_CLASSedit_proENDCLASS = {
    {
        QT_MOC_LITERAL(0, 8),  // "edit_pro"
        QT_MOC_LITERAL(9, 11),  // "pro_deleted"
        QT_MOC_LITERAL(21, 0),  // ""
        QT_MOC_LITERAL(22, 4),  // "name"
        QT_MOC_LITERAL(27, 12),  // "name_changed"
        QT_MOC_LITERAL(40, 6),  // "before"
        QT_MOC_LITERAL(47, 5),  // "after"
        QT_MOC_LITERAL(53, 17),  // "content_refreshed"
        QT_MOC_LITERAL(71, 21),  // "on_namebutton_clicked"
        QT_MOC_LITERAL(93, 21),  // "on_add_button_clicked"
        QT_MOC_LITERAL(115, 22),  // "on_deletbutton_clicked"
        QT_MOC_LITERAL(138, 17),  // "on_remove_clicked"
        QT_MOC_LITERAL(156, 17)   // "on_button_clicked"
    },
    "edit_pro",
    "pro_deleted",
    "",
    "name",
    "name_changed",
    "before",
    "after",
    "content_refreshed",
    "on_namebutton_clicked",
    "on_add_button_clicked",
    "on_deletbutton_clicked",
    "on_remove_clicked",
    "on_button_clicked"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSedit_proENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   62,    2, 0x06,    1 /* Public */,
       4,    2,   65,    2, 0x06,    3 /* Public */,
       7,    1,   70,    2, 0x06,    6 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       8,    0,   73,    2, 0x08,    8 /* Private */,
       9,    0,   74,    2, 0x08,    9 /* Private */,
      10,    0,   75,    2, 0x08,   10 /* Private */,
      11,    0,   76,    2, 0x08,   11 /* Private */,
      12,    0,   77,    2, 0x08,   12 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    5,    6,
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject edit_pro::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_CLASSedit_proENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSedit_proENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSedit_proENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<edit_pro, std::true_type>,
        // method 'pro_deleted'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'name_changed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'content_refreshed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'on_namebutton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_add_button_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_deletbutton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_remove_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_button_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void edit_pro::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<edit_pro *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->pro_deleted((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->name_changed((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 2: _t->content_refreshed((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->on_namebutton_clicked(); break;
        case 4: _t->on_add_button_clicked(); break;
        case 5: _t->on_deletbutton_clicked(); break;
        case 6: _t->on_remove_clicked(); break;
        case 7: _t->on_button_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (edit_pro::*)(QString );
            if (_t _q_method = &edit_pro::pro_deleted; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (edit_pro::*)(QString , QString );
            if (_t _q_method = &edit_pro::name_changed; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (edit_pro::*)(QString );
            if (_t _q_method = &edit_pro::content_refreshed; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject *edit_pro::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *edit_pro::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSedit_proENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int edit_pro::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void edit_pro::pro_deleted(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void edit_pro::name_changed(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void edit_pro::content_refreshed(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
