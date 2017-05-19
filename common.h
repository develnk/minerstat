#ifndef COMMON_H
#define COMMON_H

#include <QSharedPointer>

template<class T>
QMetaObject::Connection connect_from_pointer(
    const QSharedPointer<T>& sender,
    const char *signal,
    const QObject *receiver,
    const char *method,
    Qt::ConnectionType type = Qt::AutoConnection)
{
    return QObject::connect(sender.data(), signal, receiver, method, type);
}

template <typename Func1, typename Func2>
QMetaObject::Connection connect_from_pointer(
    const QSharedPointer<typename QtPrivate::FunctionPointer<Func1>::Object>& sender,
    Func1 signal,
    const typename QtPrivate::FunctionPointer<Func2>::Object *receiver,
    Func2 slot,
    Qt::ConnectionType type = Qt::AutoConnection)
{
    return QObject::connect(sender.data(), signal, receiver, slot, type);
}

template<class T>
QMetaObject::Connection connect_to_pointer(
    const QObject *sender,
    const char *signal,
    const QSharedPointer<T>& receiver,
    const char *method,
    Qt::ConnectionType type = Qt::AutoConnection)
{
    return QObject::connect(sender, signal, receiver.data(), method, type);
}

template <typename Func1, typename Func2>
QMetaObject::Connection connect_to_pointer(
    const typename QtPrivate::FunctionPointer<Func1>::Object *sender,
    Func1 signal,
    const QSharedPointer<typename QtPrivate::FunctionPointer<Func2>::Object>& receiver,
    Func2 slot,
    Qt::ConnectionType type = Qt::AutoConnection)
{
    return QObject::connect(sender, signal, receiver.data(), slot, type);
}

template<class T, class U>
QMetaObject::Connection connect_pointers(
    const QSharedPointer<T>& sender,
    const char *signal,
    const QSharedPointer<U>& receiver,
    const char *method,
    Qt::ConnectionType type = Qt::AutoConnection)
{
    return QObject::connect(sender.data(), signal, receiver.data(), method, type);
}

template <typename Func1, typename Func2>
QMetaObject::Connection connect_pointers(
    const QSharedPointer<typename QtPrivate::FunctionPointer<Func1>::Object>& sender,
    Func1 signal,
    const QSharedPointer<typename QtPrivate::FunctionPointer<Func2>::Object>& receiver,
    Func2 slot,
    Qt::ConnectionType type = Qt::AutoConnection)
{
    return QObject::connect(sender.data(), signal, receiver.data(), slot, type);
}

#endif // COMMON_H
