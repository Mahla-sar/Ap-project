/****************************************************************************
** Meta object code from reading C++ file 'edit_team.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../edit_team.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'edit_team.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSedit_teamENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSedit_teamENDCLASS = QtMocHelpers::stringData(
    "edit_team",
    "team_deleted",
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
    "on_promotebutton_clicked",
    "on_demotebutton_clicked",
    "on_button_clicked"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSedit_teamENDCLASS_t {
    uint offsetsAndSizes[30];
    char stringdata0[10];
    char stringdata1[13];
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
    char stringdata12[25];
    char stringdata13[24];
    char stringdata14[18];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSedit_teamENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSedit_teamENDCLASS_t qt_meta_stringdata_CLASSedit_teamENDCLASS = {
    {
        QT_MOC_LITERAL(0, 9),  // "edit_team"
        QT_MOC_LITERAL(10, 12),  // "team_deleted"
        QT_MOC_LITERAL(23, 0),  // ""
        QT_MOC_LITERAL(24, 4),  // "name"
        QT_MOC_LITERAL(29, 12),  // "name_changed"
        QT_MOC_LITERAL(42, 6),  // "before"
        QT_MOC_LITERAL(49, 5),  // "after"
        QT_MOC_LITERAL(55, 17),  // "content_refreshed"
        QT_MOC_LITERAL(73, 21),  // "on_namebutton_clicked"
        QT_MOC_LITERAL(95, 21),  // "on_add_button_clicked"
        QT_MOC_LITERAL(117, 22),  // "on_deletbutton_clicked"
        QT_MOC_LITERAL(140, 17),  // "on_remove_clicked"
        QT_MOC_LITERAL(158, 24),  // "on_promotebutton_clicked"
        QT_MOC_LITERAL(183, 23),  // "on_demotebutton_clicked"
        QT_MOC_LITERAL(207, 17)   // "on_button_clicked"
    },
    "edit_team",
    "team_deleted",
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
    "on_promotebutton_clicked",
    "on_demotebutton_clicked",
    "on_button_clicked"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSedit_teamENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   74,    2, 0x06,    1 /* Public */,
       4,    2,   77,    2, 0x06,    3 /* Public */,
       7,    1,   82,    2, 0x06,    6 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       8,    0,   85,    2, 0x08,    8 /* Private */,
       9,    0,   86,    2, 0x08,    9 /* Private */,
      10,    0,   87,    2, 0x08,   10 /* Private */,
      11,    0,   88,    2, 0x08,   11 /* Private */,
      12,    0,   89,    2, 0x08,   12 /* Private */,
      13,    0,   90,    2, 0x08,   13 /* Private */,
      14,    0,   91,    2, 0x08,   14 /* Private */,

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
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject edit_team::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_CLASSedit_teamENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSedit_teamENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSedit_teamENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<edit_team, std::true_type>,
        // method 'team_deleted'
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
        // method 'on_promotebutton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_demotebutton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_button_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void edit_team::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<edit_team *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->team_deleted((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->name_changed((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 2: _t->content_refreshed((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->on_namebutton_clicked(); break;
        case 4: _t->on_add_button_clicked(); break;
        case 5: _t->on_deletbutton_clicked(); break;
        case 6: _t->on_remove_clicked(); break;
        case 7: _t->on_promotebutton_clicked(); break;
        case 8: _t->on_demotebutton_clicked(); break;
        case 9: _t->on_button_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (edit_team::*)(QString );
            if (_t _q_method = &edit_team::team_deleted; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (edit_team::*)(QString , QString );
            if (_t _q_method = &edit_team::name_changed; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (edit_team::*)(QString );
            if (_t _q_method = &edit_team::content_refreshed; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject *edit_team::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *edit_team::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSedit_teamENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int edit_team::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void edit_team::team_deleted(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void edit_team::name_changed(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void edit_team::content_refreshed(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
