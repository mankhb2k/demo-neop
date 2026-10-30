/****************************************************************************
** Meta object code from reading C++ file 'video_player_controller.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../video_player_controller.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'video_player_controller.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.12.0. It"
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
struct qt_meta_tag_ZN21VideoPlayerControllerE_t {};
} // unnamed namespace

template <> constexpr inline auto VideoPlayerController::qt_create_metaobjectdata<qt_meta_tag_ZN21VideoPlayerControllerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "VideoPlayerController",
        "sourceChanged",
        "",
        "playingChanged",
        "seekableChanged",
        "positionChanged",
        "durationChanged",
        "volumeChanged",
        "mutedChanged",
        "statusTextChanged",
        "errorMessageChanged",
        "openFile",
        "QUrl",
        "url",
        "setVideoSink",
        "QVideoSink*",
        "sink",
        "togglePlayback",
        "stop",
        "seekTo",
        "position",
        "setVolume",
        "volume",
        "setMuted",
        "muted",
        "hasSource",
        "sourceName",
        "playing",
        "seekable",
        "duration",
        "statusText",
        "errorMessage"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'sourceChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'playingChanged'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'seekableChanged'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'positionChanged'
        QtMocHelpers::SignalData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'durationChanged'
        QtMocHelpers::SignalData<void()>(6, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'volumeChanged'
        QtMocHelpers::SignalData<void()>(7, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'mutedChanged'
        QtMocHelpers::SignalData<void()>(8, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'statusTextChanged'
        QtMocHelpers::SignalData<void()>(9, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'errorMessageChanged'
        QtMocHelpers::SignalData<void()>(10, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'openFile'
        QtMocHelpers::MethodData<void(const QUrl &)>(11, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 12, 13 },
        }}),
        // Method 'setVideoSink'
        QtMocHelpers::MethodData<void(QVideoSink *)>(14, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 15, 16 },
        }}),
        // Method 'togglePlayback'
        QtMocHelpers::MethodData<void()>(17, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'stop'
        QtMocHelpers::MethodData<void()>(18, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'seekTo'
        QtMocHelpers::MethodData<void(qint64)>(19, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::LongLong, 20 },
        }}),
        // Method 'setVolume'
        QtMocHelpers::MethodData<void(qreal)>(21, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QReal, 22 },
        }}),
        // Method 'setMuted'
        QtMocHelpers::MethodData<void(bool)>(23, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 24 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'hasSource'
        QtMocHelpers::PropertyData<bool>(25, QMetaType::Bool, QMC::DefaultPropertyFlags, 0),
        // property 'sourceName'
        QtMocHelpers::PropertyData<QString>(26, QMetaType::QString, QMC::DefaultPropertyFlags, 0),
        // property 'playing'
        QtMocHelpers::PropertyData<bool>(27, QMetaType::Bool, QMC::DefaultPropertyFlags, 1),
        // property 'seekable'
        QtMocHelpers::PropertyData<bool>(28, QMetaType::Bool, QMC::DefaultPropertyFlags, 2),
        // property 'position'
        QtMocHelpers::PropertyData<qint64>(20, QMetaType::LongLong, QMC::DefaultPropertyFlags, 3),
        // property 'duration'
        QtMocHelpers::PropertyData<qint64>(29, QMetaType::LongLong, QMC::DefaultPropertyFlags, 4),
        // property 'volume'
        QtMocHelpers::PropertyData<qreal>(22, QMetaType::QReal, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 5),
        // property 'muted'
        QtMocHelpers::PropertyData<bool>(24, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 6),
        // property 'statusText'
        QtMocHelpers::PropertyData<QString>(30, QMetaType::QString, QMC::DefaultPropertyFlags, 7),
        // property 'errorMessage'
        QtMocHelpers::PropertyData<QString>(31, QMetaType::QString, QMC::DefaultPropertyFlags, 8),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<VideoPlayerController, qt_meta_tag_ZN21VideoPlayerControllerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject VideoPlayerController::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN21VideoPlayerControllerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN21VideoPlayerControllerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN21VideoPlayerControllerE_t>.metaTypes,
    nullptr
} };

void VideoPlayerController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<VideoPlayerController *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->sourceChanged(); break;
        case 1: _t->playingChanged(); break;
        case 2: _t->seekableChanged(); break;
        case 3: _t->positionChanged(); break;
        case 4: _t->durationChanged(); break;
        case 5: _t->volumeChanged(); break;
        case 6: _t->mutedChanged(); break;
        case 7: _t->statusTextChanged(); break;
        case 8: _t->errorMessageChanged(); break;
        case 9: _t->openFile((*reinterpret_cast<std::add_pointer_t<QUrl>>(_a[1]))); break;
        case 10: _t->setVideoSink((*reinterpret_cast<std::add_pointer_t<QVideoSink*>>(_a[1]))); break;
        case 11: _t->togglePlayback(); break;
        case 12: _t->stop(); break;
        case 13: _t->seekTo((*reinterpret_cast<std::add_pointer_t<qint64>>(_a[1]))); break;
        case 14: _t->setVolume((*reinterpret_cast<std::add_pointer_t<qreal>>(_a[1]))); break;
        case 15: _t->setMuted((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QVideoSink* >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (VideoPlayerController::*)()>(_a, &VideoPlayerController::sourceChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (VideoPlayerController::*)()>(_a, &VideoPlayerController::playingChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (VideoPlayerController::*)()>(_a, &VideoPlayerController::seekableChanged, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (VideoPlayerController::*)()>(_a, &VideoPlayerController::positionChanged, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (VideoPlayerController::*)()>(_a, &VideoPlayerController::durationChanged, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (VideoPlayerController::*)()>(_a, &VideoPlayerController::volumeChanged, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (VideoPlayerController::*)()>(_a, &VideoPlayerController::mutedChanged, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (VideoPlayerController::*)()>(_a, &VideoPlayerController::statusTextChanged, 7))
            return;
        if (QtMocHelpers::indexOfMethod<void (VideoPlayerController::*)()>(_a, &VideoPlayerController::errorMessageChanged, 8))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<bool*>(_v) = _t->hasSource(); break;
        case 1: *reinterpret_cast<QString*>(_v) = _t->sourceName(); break;
        case 2: *reinterpret_cast<bool*>(_v) = _t->playing(); break;
        case 3: *reinterpret_cast<bool*>(_v) = _t->seekable(); break;
        case 4: *reinterpret_cast<qint64*>(_v) = _t->position(); break;
        case 5: *reinterpret_cast<qint64*>(_v) = _t->duration(); break;
        case 6: *reinterpret_cast<qreal*>(_v) = _t->volume(); break;
        case 7: *reinterpret_cast<bool*>(_v) = _t->muted(); break;
        case 8: *reinterpret_cast<QString*>(_v) = _t->statusText(); break;
        case 9: *reinterpret_cast<QString*>(_v) = _t->errorMessage(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 6: _t->setVolume(*reinterpret_cast<qreal*>(_v)); break;
        case 7: _t->setMuted(*reinterpret_cast<bool*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *VideoPlayerController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VideoPlayerController::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN21VideoPlayerControllerE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int VideoPlayerController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void VideoPlayerController::sourceChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void VideoPlayerController::playingChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void VideoPlayerController::seekableChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void VideoPlayerController::positionChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void VideoPlayerController::durationChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void VideoPlayerController::volumeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void VideoPlayerController::mutedChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void VideoPlayerController::statusTextChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void VideoPlayerController::errorMessageChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}
QT_WARNING_POP
