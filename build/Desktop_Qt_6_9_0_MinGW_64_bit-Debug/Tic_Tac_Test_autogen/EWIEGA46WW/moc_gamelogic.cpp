/****************************************************************************
** Meta object code from reading C++ file 'gamelogic.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../gamelogic.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gamelogic.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.0. It"
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
struct qt_meta_tag_ZN9GameLogicE_t {};
} // unnamed namespace

template <> constexpr inline auto GameLogic::qt_create_metaobjectdata<qt_meta_tag_ZN9GameLogicE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "GameLogic",
        "gameOver",
        "",
        "Player",
        "winner",
        "currentPlayerChanged",
        "player",
        "moveMade",
        "row",
        "col"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'gameOver'
        QtMocHelpers::SignalData<void(Player)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
        // Signal 'currentPlayerChanged'
        QtMocHelpers::SignalData<void(Player)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 6 },
        }}),
        // Signal 'moveMade'
        QtMocHelpers::SignalData<void(int, int, Player)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 8 }, { QMetaType::Int, 9 }, { 0x80000000 | 3, 6 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<GameLogic, qt_meta_tag_ZN9GameLogicE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject GameLogic::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN9GameLogicE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN9GameLogicE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN9GameLogicE_t>.metaTypes,
    nullptr
} };

void GameLogic::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<GameLogic *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->gameOver((*reinterpret_cast< std::add_pointer_t<Player>>(_a[1]))); break;
        case 1: _t->currentPlayerChanged((*reinterpret_cast< std::add_pointer_t<Player>>(_a[1]))); break;
        case 2: _t->moveMade((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<Player>>(_a[3]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (GameLogic::*)(Player )>(_a, &GameLogic::gameOver, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (GameLogic::*)(Player )>(_a, &GameLogic::currentPlayerChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (GameLogic::*)(int , int , Player )>(_a, &GameLogic::moveMade, 2))
            return;
    }
}

const QMetaObject *GameLogic::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GameLogic::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN9GameLogicE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int GameLogic::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void GameLogic::gameOver(Player _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void GameLogic::currentPlayerChanged(Player _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void GameLogic::moveMade(int _t1, int _t2, Player _t3)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1, _t2, _t3);
}
QT_WARNING_POP
